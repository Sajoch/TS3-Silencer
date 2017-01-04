ifeq ($(OS),LINUX)
	CROSS_COMPILE=
	CROSS_COMPILE32=
endif
ifeq ($(OS), WIN32)
	CROSS_COMPILE=i686-w64-mingw32-
	CROSS_COMPILE32=i686-w64-mingw32-
else
	CROSS_COMPILE=x86_64-w64-mingw32-
	CROSS_COMPILE32=i686-w64-mingw32-
endif
export CXX=$(CROSS_COMPILE)g++
export GCC=$(CROSS_COMPILE)gcc
export CXX32=$(CROSS_COMPILE32)g++
export GCC32=$(CROSS_COMPILE32)gcc
CPPFLAG= --std=c++11 -Ipluginsdk/include
CFLAG= --std=c11 -Ipluginsdk/include
PROGRAM=build/TS3Silencer.dll

all: obj build $(PROGRAM)

obj/%.o : src/%.cpp
	@echo "-Compile" $@
	@$(CXX) -c -Wall -o $@ $(CPPFLAG) $<

obj/%.o : src/%.c
	@echo "-Compile" $@
	@$(GCC) -c -Wall -o $@ $(CFLAG) $<


obj:
	mkdir -p obj

build:
	mkdir -p build

OBJS=main export

OBJECTS=$(patsubst %,obj/%.o,$(OBJS))

obj/main.o: src/main.cpp src/main.h
obj/export.o: src/export.cpp src/export.h
$(PROGRAM): $(OBJECTS)
	@echo "============ Compile" $@ "=============="
	@$(CXX) -shared $^ -o $@ $(CPPFLAG)

test: all
	cp $(PROGRAM) F:\Programy\TeamSpeak3_64\plugins

clean:
	$(rm obj || true)
	$(rm build || true)