#include "parse_json.h"




int main(int argc ,char**argv)
{
    if(argc!=2){std::cout<<"Only takes one arg!!"<<std::flush; exit(EXIT_FAILURE);}
    std::cout<<JSON::stringify(JSON::parse_file(argv[1]))<<std::endl;

    return 0;
}