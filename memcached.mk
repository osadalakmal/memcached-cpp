##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=memcached
ConfigurationName      :=Debug
WorkspacePath          := "/home/osada/prog/memcached-cpp"
ProjectPath            := "/home/osada/prog/memcached-cpp"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=osada
Date                   :=28/10/12
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
ObjectsFileList        :="/home/osada/prog/memcached-cpp/memcached.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -Wl,-rpath -Wl,/usr/local/lib/ -lprotobuf
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/home/osada/prog/gtest/include/ $(IncludeSwitch)/usr/local/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)memcached $(LibrarySwitch)snappy 
ArLibs                 :=  "libmemcached.a" "libsnappy.a" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/lib/ 

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
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/mc_server_handle$(ObjectSuffix) $(IntermediateDirectory)/mc_server_proto_stream$(ObjectSuffix) 

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
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/osada/prog/memcached-cpp/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/osada/prog/memcached-cpp/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/osada/prog/memcached-cpp/main.cpp"

$(IntermediateDirectory)/mc_server_handle$(ObjectSuffix): mc_server_handle.cpp $(IntermediateDirectory)/mc_server_handle$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/osada/prog/memcached-cpp/mc_server_handle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mc_server_handle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mc_server_handle$(DependSuffix): mc_server_handle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mc_server_handle$(ObjectSuffix) -MF$(IntermediateDirectory)/mc_server_handle$(DependSuffix) -MM "/home/osada/prog/memcached-cpp/mc_server_handle.cpp"

$(IntermediateDirectory)/mc_server_handle$(PreprocessSuffix): mc_server_handle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mc_server_handle$(PreprocessSuffix) "/home/osada/prog/memcached-cpp/mc_server_handle.cpp"

$(IntermediateDirectory)/mc_server_proto_stream$(ObjectSuffix): mc_server_proto_stream.cpp $(IntermediateDirectory)/mc_server_proto_stream$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/osada/prog/memcached-cpp/mc_server_proto_stream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mc_server_proto_stream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mc_server_proto_stream$(DependSuffix): mc_server_proto_stream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mc_server_proto_stream$(ObjectSuffix) -MF$(IntermediateDirectory)/mc_server_proto_stream$(DependSuffix) -MM "/home/osada/prog/memcached-cpp/mc_server_proto_stream.cpp"

$(IntermediateDirectory)/mc_server_proto_stream$(PreprocessSuffix): mc_server_proto_stream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mc_server_proto_stream$(PreprocessSuffix) "/home/osada/prog/memcached-cpp/mc_server_proto_stream.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_handle$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_handle$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_handle$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_proto_stream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_proto_stream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mc_server_proto_stream$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/osada/prog/memcached-cpp/.build-debug/memcached"


