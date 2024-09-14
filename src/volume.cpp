#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>
#include "arguments.hpp"

int main(int argc, char** argv) {

    /* Parse arguments to determine behavior */
    if(parseArgs(argv, argc) != SUCCESS)
    {
        return -1;
    }

    HRESULT hr;

    // Initialize COM library
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::cerr << "Failed to initialize COM library. Error code: 0x" << std::hex << hr << std::endl;
        return -1;
    }

    // Create the device enumerator
    IMMDeviceEnumerator* pEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr)) {
        std::cerr << "Failed to create IMMDeviceEnumerator. Error code: 0x" << std::hex << hr << std::endl;
        CoUninitialize();
        return -1;
    }

    // Get the default audio endpoint
    IMMDevice* pDevice = NULL;
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    pEnumerator->Release();  // Release the enumerator object
    if (FAILED(hr)) {
        std::cerr << "Failed to get default audio endpoint. Error code: 0x" << std::hex << hr << std::endl;
        CoUninitialize();
        return -1;
    }

    // Get the IAudioEndpointVolume interface
    IAudioEndpointVolume* pVolume = NULL;
    hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (void**)&pVolume);
    pDevice->Release();  // Release the device object
    if (FAILED(hr)) {
        std::cerr << "Failed to get IAudioEndpointVolume interface. Error code: 0x" << std::hex << hr << std::endl;
        CoUninitialize();
        return -1;
    }

    if (args.query) {
        // Query the current master volume level
        float currentVolume = 0.0f;
        hr = pVolume->GetMasterVolumeLevelScalar(&currentVolume);
        if (FAILED(hr)) {
            std::cerr << "Failed to get master volume. Error code: 0x" << std::hex << hr << std::endl;
            pVolume->Release();  // Release the volume object
            CoUninitialize();
            return -1;
        }

        // Print the current volume level
        std::cout << "Current volume level: " << (currentVolume * 100) << "%" << std::endl;
    }


    // Set the master volume (0.0 = mute, 1.0 = max volume)
    if(args.set)
    {
        hr = pVolume->SetMasterVolumeLevelScalar(args.set_val, NULL);
        if (FAILED(hr)) {
            std::cerr << "Failed to set master volume. Error code: 0x" << std::hex << hr << std::endl;
            pVolume->Release();  // Release the volume object
            CoUninitialize();
            return -1;
        }

        std::cout << "Set volume to " << (args.set_val * 100) << "%" << std::endl;
    }

    // Clean up
    pVolume->Release();
    CoUninitialize();

    return 0;
}
