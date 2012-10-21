##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=memcached_test
ConfigurationName      :=Debug
WorkspacePath          := "/home/osada/prog/memcached"
ProjectPath            := "/home/osada/prog/memcached/memcached_test"
IntermediateDirectory  :=Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=osada
Date                   :=21/10/12
CodeLitePath           :="/home/osada/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/osada/prog/memcached/memcached_test/memcached_test.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -Wl,-rpath -Wl,/usr/local/lib/ -lmemcached 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)$(GTEST_INC_PATH) $(IncludeSwitch). $(IncludeSwitch)/usr/local/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gtest $(LibrarySwitch)pthread ../Debug/mc_server_handle.o $(LibrarySwitch)memcached $(LibrarySwitch)snappy 
ArLibs                 :=  "gtest" "pthread ../Debug/mc_server_handle.o" "libmemcached.a" "libsnappy.a" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/home/osada/prog/gtest/lib/ $(LibraryPathSwitch)/usr/local/lib/ 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall -std=c++0x $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/mc_server_handle.t$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d Debug || $(MakeDirCommand) Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/osada/prog/memcached/memcached_test/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/osada/prog/memcached/memcached_test/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/osada/prog/memcached/memcached_test/main.cpp"

$(IntermediateDirectory)/mc_server_handle.t$(ObjectSuffix): mc_server_handle.t.cpp $(IntermediateDirectory)/mc_server_handle.t$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/osada/prog/memcached/memcached_test/mc_server_handle.t.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mc_server_handle.t$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mc_server_handle.t$(DependSuffix): mc_server_handle.t.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mc_server_handle.t$(ObjectSuffix) -MF$(IntermediateDirectory)/mc_server_handle.t$(DependSuffix) -MM "/home/osada/prog/memcached/memcached_test/mc_server_handle.t.cpp"

$(IntermediateDirectory)/mc_server_handle.t$(PreprocessSuffix): mc_server_handle.t.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mc_server_handle.t$(PreprocessSuffix) "/home/osada/prog/memcached/memcached_test/mc_server_handle.t.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_handle.t$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_handle.t$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_handle.t$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/osada/prog/memcached/.build-debug/memcached_test"


