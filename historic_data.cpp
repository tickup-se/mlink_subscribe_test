#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

#include "mio.h"
#include "ticker_list.h"

int handle_error(const std::error_code& error)
{
    const auto& errmsg = error.message();
    std::printf("error mapping file: %s, exiting...\n", errmsg.c_str());
    return error.value();
}

std::map<std::string, uint64_t> getLookUpTable(std::string lFileName) {
    std::string lLine;
    std::ifstream file(lFileName);

    if (!file.is_open()) {
        std::cout << "error opening file" << std::endl;
        return {};
    }

    std::map<std::string, uint64_t> lLookUpTable;

    //parse header
    getline(file, lLine);
    std::stringstream lOriginalObjects(lLine);
    std::string lColumnName;
    uint64_t lColumnIndex = 0;
    while (getline(lOriginalObjects, lColumnName, '\t')) {
        lColumnName.erase( std::remove(lColumnName.begin(), lColumnName.end(), '\r'), lColumnName.end() );
        lLookUpTable[lColumnName] = lColumnIndex++;
    }
    return lLookUpTable;
}

int main(int argc, char *argv[]) {

    //Get the program arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <FILE_NAME>" << std::endl;
        return EXIT_FAILURE;
    }

    //Get the filename of SpiderRocks historic prints file
    std::string lFileName = argv[1];

    //print the column index number for each column name.
    std::map<std::string, uint64_t> lLookUpTable = getLookUpTable(lFileName);
    for (auto& [key, value] : lLookUpTable) {
        std::cout << key << " " << value << std::endl;
    }

    //Get the ticker list for the universe we target
    auto lTickerList = getTickerVector();

    //Memory map the file
    std::error_code error;
    mio::mmap_source ro_mmap;
    ro_mmap.map(lFileName, error);
    if (error) {
        return handle_error(error);
    }

    //initiate the variables
    auto pData = ro_mmap.data();
    uint64_t lRow = 0;
    uint64_t lColumnIndex = 0;
    uint64_t lNumberOpenCrosses = 0;
    uint64_t lNumberCloseCrosses = 0;
    std::map<std::string, bool> lUniqueOpenCrosses;
    std::map<std::string, bool> lUniqueCloseCrosses;
    uint64_t lNumberOpenCrossesNoFilter = 0;
    uint64_t lNumberCloseCrossesNoFilter = 0;
    std::map<std::string, bool> lUniqueOpenCrossesNoFilter;
    std::map<std::string, bool> lUniqueCloseCrossesNoFilter;
    bool lCurrentRowIsNYSE = false;
    std::string lTickerName;
    std::string lTimestamp;

    //Skip the first line (it's the column names)
    size_t lSkipLength = 0;
    for (size_t i = 0; i < ro_mmap.size(); ++i) {
        if (pData[i] == '\r') {
            lSkipLength = i + 2;
            break;
        }
    }
    mio::mmap_source::const_pointer pCellStart = pData + lSkipLength;


    //Loop through each line in the CSV and extract the data from the relevant cells
    for (size_t i = lSkipLength; i < ro_mmap.size(); ++i) {
        if (pData[i] == '\r') {
            lCurrentRowIsNYSE = false;
            pCellStart = pData + i + 1;
            lColumnIndex = 0;
            lRow++;
            if (lRow % 100000 == 0) {
                std::cout << "parsed " << lRow << " rows" << std::endl;
            }
        } else if (pData[i] == '\t') {

            //Debug output raw data
            //std::string_view lTest(pCellStart,(pData+i)-pCellStart);
            //std::cout << lTest << " Cidx:" << lColumnIndex <<std::endl;

            //Get the ticker name
            if (lColumnIndex == 2) {
                lTickerName = std::string(pCellStart,(pData+i)-pCellStart);
            }


            //Get the timestamp
            if (lColumnIndex == 3) {
                lTimestamp = std::string(pCellStart,(pData+i)-pCellStart);
            }

            //Get the exchange
            if (lColumnIndex == 7) {
                if (*(const char*)pCellStart == 'N' &&
                    *(const char*)(pCellStart + 1) == 'Y' &&
                    *(const char*)(pCellStart + 2) == 'S' &&
                    *(const char*)(pCellStart + 3) == 'E' &&
                    *(const char*)(pCellStart + 4) == '\t') {
                    lCurrentRowIsNYSE = true;
                }
            }

            //If NYSE and if the condition is open or close
            if (lColumnIndex == 16 && lCurrentRowIsNYSE) {
                if (*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') {
                    //std::cout << "Found open cross (name):" << lTickerName << std::endl;
                    lNumberOpenCrossesNoFilter++;
                    lUniqueOpenCrossesNoFilter[lTickerName] = true;
                    for (auto &rTickerFromList : lTickerList) {
                        if (rTickerFromList == lTickerName) {
                            std::cout << "Found open cross (ticker):" << rTickerFromList << " " << lTimestamp << std::endl;
                            lNumberOpenCrosses++;
                            lUniqueOpenCrosses[lTickerName] = true;
                        }
                    }
                }
                if (*(const char*)pCellStart == '5' && *(const char*)(pCellStart + 1) == '4') {
                    //std::cout << "Found close cross (name):" << lTickerName << std::endl;
                    lNumberCloseCrossesNoFilter++;
                    lUniqueCloseCrossesNoFilter[lTickerName] = true;
                    for (auto &rTickerFromList : lTickerList) {
                        if (rTickerFromList == lTickerName) {
                            std::cout << "Found close cross (ticker):" << rTickerFromList << " " << lTimestamp << std::endl;
                            lNumberCloseCrosses++;
                            lUniqueCloseCrosses[lTickerName] = true;
                        }
                    }
                }
            }

            //open or close prints should not occur in this print code position
            if (lColumnIndex == 15 && lCurrentRowIsNYSE) {
                if ((*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') || (*(const char*)pCellStart == '5' && *(const char*)(pCellStart + 1) == '4')) {
                    throw std::runtime_error("Found open or close cross at wrong position");
                }
            }

            //open or close prints should not occur in this print code position
            if (lColumnIndex == 17 && lCurrentRowIsNYSE) {
                if ((*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') || (*(const char*)pCellStart == '5' && *(const char*)(pCellStart + 1) == '4')) {
                    throw std::runtime_error("Found open or close cross at wrong position");
                }
            }

            //open or close prints should not occur in this print code position
            if (lColumnIndex == 18 && lCurrentRowIsNYSE) {
                if ((*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') || (*(const char*)pCellStart == '5' && *(const char*)(pCellStart + 1) == '4')) {
                    throw std::runtime_error("Found open or close cross at wrong position");
                }
            }

            //advance to next cell
            pCellStart = pData + i + 1;
            lColumnIndex++;
        }
    }

    std::cout << "(filtered) Number of open crosses: " << lNumberOpenCrosses << std::endl;
    std::cout << "(filtered) Number of close crosses: " << lNumberCloseCrosses << std::endl;
    std::cout << "(filtered) Unique open crosses: " << lUniqueOpenCrosses.size() << std::endl;
    std::cout << "(filtered) Unique close crosses: " << lUniqueCloseCrosses.size() << std::endl << std::endl;
    std::cout << "(No filter) Number of open crosses: " << lNumberOpenCrossesNoFilter << std::endl;
    std::cout << "(No filter) Number of close crosses: " << lNumberCloseCrossesNoFilter << std::endl;
    std::cout << "(No filter) Unique open crosses: " << lUniqueOpenCrossesNoFilter.size() << std::endl;
    std::cout << "(No filter) Unique close crosses: " << lUniqueCloseCrossesNoFilter.size() << std::endl;

    //save a file named open_trades.txt containing all lUniqueOpenCrosses contained ticker names sorted in alphabetic order
    std::ofstream lTradesFile;
    lTradesFile.open ("open_trades.txt");
    for (auto &rTickerFromList : lUniqueOpenCrosses) {
        lTradesFile << rTickerFromList.first << std::endl;
    }
    lTradesFile.close();
    std::cout << "Saved open_trades.txt" << std::endl;

    //Same for close trades
    lTradesFile.open ("close_trades.txt");
    for (auto &rTickerFromList : lUniqueCloseCrosses) {
        lTradesFile << rTickerFromList.first << std::endl;
    }
    lTradesFile.close();
    std::cout << "Saved close_trades.txt" << std::endl;

    ro_mmap.unmap();
    return EXIT_SUCCESS;
}