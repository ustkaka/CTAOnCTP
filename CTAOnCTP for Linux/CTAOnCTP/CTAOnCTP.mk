##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CTAOnCTP
ConfigurationName      :=Debug
WorkspacePath          := "/home/xiaoshiquan/Workspaces/CTAOnCTP"
ProjectPath            := "/home/xiaoshiquan/Workspaces/CTAOnCTP/CTAOnCTP"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=xiaoshiquan
Date                   :=21/10/17
CodeLitePath           :="/home/xiaoshiquan/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
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
ObjectsFileList        :="CTAOnCTP.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            := -Wl,-lthostmduserapi,-lthosttraderapi 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./CTP $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++11 -Wall -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/CSimpleMdSpi.cpp$(ObjectSuffix) $(IntermediateDirectory)/CSimpleTraderSpi.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/xiaoshiquan/Workspaces/CTAOnCTP/CTAOnCTP/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/CSimpleMdSpi.cpp$(ObjectSuffix): CSimpleMdSpi.cpp $(IntermediateDirectory)/CSimpleMdSpi.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/xiaoshiquan/Workspaces/CTAOnCTP/CTAOnCTP/CSimpleMdSpi.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CSimpleMdSpi.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CSimpleMdSpi.cpp$(DependSuffix): CSimpleMdSpi.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CSimpleMdSpi.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CSimpleMdSpi.cpp$(DependSuffix) -MM "CSimpleMdSpi.cpp"

$(IntermediateDirectory)/CSimpleMdSpi.cpp$(PreprocessSuffix): CSimpleMdSpi.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CSimpleMdSpi.cpp$(PreprocessSuffix) "CSimpleMdSpi.cpp"

$(IntermediateDirectory)/CSimpleTraderSpi.cpp$(ObjectSuffix): CSimpleTraderSpi.cpp $(IntermediateDirectory)/CSimpleTraderSpi.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/xiaoshiquan/Workspaces/CTAOnCTP/CTAOnCTP/CSimpleTraderSpi.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CSimpleTraderSpi.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CSimpleTraderSpi.cpp$(DependSuffix): CSimpleTraderSpi.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CSimpleTraderSpi.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CSimpleTraderSpi.cpp$(DependSuffix) -MM "CSimpleTraderSpi.cpp"

$(IntermediateDirectory)/CSimpleTraderSpi.cpp$(PreprocessSuffix): CSimpleTraderSpi.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CSimpleTraderSpi.cpp$(PreprocessSuffix) "CSimpleTraderSpi.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


