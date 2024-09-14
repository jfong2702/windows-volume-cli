# Microsoft NMAKE makefile

LIBRARIES="C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64\User32.Lib"\
"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64\Ole32.Lib"\
"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64\Uuid.Lib"

CFILES=src^\volume.cpp src^\arguments.cpp 
OUTPUT_NAME=volume.exe
CPP_FLAGS=/EHsc

all: $(OUTPUT_NAME)

$(OUTPUT_NAME): $(CFILES)
	cl $(CFILES) $(CPP_FLAGS) $(LIBRARIES) /Fe$(OUTPUT_NAME)

# use nmake release VERSION=X.X.X
release:
	copy $(OUTPUT_NAME) bin^\"volume_$(VERSION).exe"

clean:
	del $(OUTPUT_NAME)
	del *.obj
