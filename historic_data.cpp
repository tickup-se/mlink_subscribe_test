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

    //API Key
    std::string lFileName = argv[1];
    std::map<std::string, uint64_t> lLookUpTable = getLookUpTable(lFileName);
    auto lTickerList = getTickerVector();

    for (auto& [key, value] : lLookUpTable) {
        std::cout << key << " " << value << std::endl;
    }

    std::error_code error;
    mio::mmap_source ro_mmap;
    ro_mmap.map(lFileName, error);
    if (error) {
        return handle_error(error);
    }

    auto pData = ro_mmap.data();
    uint64_t lRow = 0;
    uint64_t lColumnIndex = 0;

    //Skip first line
    size_t lSkipLength = 0;
    for (size_t i = 0; i < ro_mmap.size(); ++i) {
        if (pData[i] == '\r') {
            lSkipLength = i + 2;
            break;
        }
    }

    uint64_t lNumberOpenCrosses = 0;

    bool lCurrentRowIsNYSE = false;
    mio::mmap_source::const_pointer pCellStart = pData + lSkipLength;
    std::string lTickerName;
    for (size_t i = lSkipLength; i < ro_mmap.size(); ++i) {
        if (pData[i] == '\r') {
            lCurrentRowIsNYSE = false;
            pCellStart = pData + i + 1;
            lColumnIndex = 0;
            lRow++;
            if (lRow % 100000 == 0) {
                std::cout << "read " << lRow << " rows" << std::endl;
            }
        } else if (pData[i] == '\t') {
            //std::string_view lTest(pCellStart,(pData+i)-pCellStart);
            //std::cout << lTest << " Cidx:" << lColumnIndex <<std::endl;


            if (lColumnIndex == 2) {
                lTickerName = std::string(pCellStart,(pData+i)-pCellStart);
            }


            if (lColumnIndex == 7) {
                if (*(const char*)pCellStart == 'N' &&
                    *(const char*)(pCellStart + 1) == 'Y' &&
                    *(const char*)(pCellStart + 2) == 'S' &&
                    *(const char*)(pCellStart + 3) == 'E' &&
                    *(const char*)(pCellStart + 4) == '\t') {
                    lCurrentRowIsNYSE = true;
                }
            }

            if (lColumnIndex == 16 && lCurrentRowIsNYSE) {
                if (*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') {
                    //std::cout << "Found open cross (name):" << lTickerName << std::endl;
                    for (auto &rTickerFromList : lTickerList) {
                        if (rTickerFromList == lTickerName) {
                            std::cout << "Found open cross (ticker):" << rTickerFromList << std::endl;
                            lNumberOpenCrosses++;
                        }
                    }
                }
            }

            if (lColumnIndex == 15 && lCurrentRowIsNYSE) {
                if (*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') {
                    throw std::runtime_error("Found open cross");
                }
            }

            if (lColumnIndex == 17 && lCurrentRowIsNYSE) {
                if (*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') {
                    throw std::runtime_error("Found open cross");
                }
            }

            if (lColumnIndex == 18 && lCurrentRowIsNYSE) {
                if (*(const char*)pCellStart == '7' && *(const char*)(pCellStart + 1) == '9') {
                    throw std::runtime_error("Found open cross");
                }
            }

            //For next cell
            pCellStart = pData + i + 1;
            lColumnIndex++;
        }
    }

    std::cout << "Number of open crosses: " << lNumberOpenCrosses << std::endl;

    ro_mmap.unmap();
    return EXIT_SUCCESS;
}