#include "parse_json.h"




int main(int argc ,char**argv)
{
    if(argc!=2){std::cout<<"Only takes one arg!!"<<std::flush; exit(EXIT_FAILURE);}
    std::cout<<JSON::parseJson(JSON::parseFile(argv[1]))<<std::endl;

    return 0;
}