#include <src/config/MyPrgConfig.h>
#include <iostream>
#include "include/inc.h"
#ifdef USE_SOME_LIB
//    #include <>
#endif

int main(){
#ifdef USE_SOME_LIB
    	std::cout << "Versionq: " << PRG_VERSION_MAJOR << std::endl;
#endif
#ifndef USE_SOME_LIB
	std::cout << "asdasd" << std::endl;
#endif
}
