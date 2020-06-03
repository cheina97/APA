##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=E09x3
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/valte/Documents/APA/2018-2019
ProjectPath            :=C:/Users/valte/Documents/APA/2018-2019/E09x3
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=valte
Date                   :=16/12/2018
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
ObjectsFileList        :="E09x3.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/equipArray.c$(ObjectSuffix) $(IntermediateDirectory)/invArray.c$(ObjectSuffix) $(IntermediateDirectory)/pgList.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/pg.c$(ObjectSuffix) $(IntermediateDirectory)/inv.c$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/equipArray.c$(ObjectSuffix): equipArray.c $(IntermediateDirectory)/equipArray.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/valte/Documents/APA/2018-2019/E09x3/equipArray.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/equipArray.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/equipArray.c$(DependSuffix): equipArray.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/equipArray.c$(ObjectSuffix) -MF$(IntermediateDirectory)/equipArray.c$(DependSuffix) -MM equipArray.c

$(IntermediateDirectory)/equipArray.c$(PreprocessSuffix): equipArray.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/equipArray.c$(PreprocessSuffix) equipArray.c

$(IntermediateDirectory)/invArray.c$(ObjectSuffix): invArray.c $(IntermediateDirectory)/invArray.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/valte/Documents/APA/2018-2019/E09x3/invArray.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/invArray.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/invArray.c$(DependSuffix): invArray.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/invArray.c$(ObjectSuffix) -MF$(IntermediateDirectory)/invArray.c$(DependSuffix) -MM invArray.c

$(IntermediateDirectory)/invArray.c$(PreprocessSuffix): invArray.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/invArray.c$(PreprocessSuffix) invArray.c

$(IntermediateDirectory)/pgList.c$(ObjectSuffix): pgList.c $(IntermediateDirectory)/pgList.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/valte/Documents/APA/2018-2019/E09x3/pgList.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pgList.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pgList.c$(DependSuffix): pgList.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pgList.c$(ObjectSuffix) -MF$(IntermediateDirectory)/pgList.c$(DependSuffix) -MM pgList.c

$(IntermediateDirectory)/pgList.c$(PreprocessSuffix): pgList.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pgList.c$(PreprocessSuffix) pgList.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/valte/Documents/APA/2018-2019/E09x3/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/pg.c$(ObjectSuffix): pg.c $(IntermediateDirectory)/pg.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/valte/Documents/APA/2018-2019/E09x3/pg.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pg.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pg.c$(DependSuffix): pg.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pg.c$(ObjectSuffix) -MF$(IntermediateDirectory)/pg.c$(DependSuffix) -MM pg.c

$(IntermediateDirectory)/pg.c$(PreprocessSuffix): pg.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pg.c$(PreprocessSuffix) pg.c

$(IntermediateDirectory)/inv.c$(ObjectSuffix): inv.c $(IntermediateDirectory)/inv.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/valte/Documents/APA/2018-2019/E09x3/inv.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/inv.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/inv.c$(DependSuffix): inv.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/inv.c$(ObjectSuffix) -MF$(IntermediateDirectory)/inv.c$(DependSuffix) -MM inv.c

$(IntermediateDirectory)/inv.c$(PreprocessSuffix): inv.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/inv.c$(PreprocessSuffix) inv.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


