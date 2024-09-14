#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>

int main() {
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

    // Set the master volume (0.0 = mute, 1.0 = max volume)
    float newVolume = 0.5f;  // 50% volume
    hr = pVolume->SetMasterVolumeLevelScalar(newVolume, NULL);
    if (FAILED(hr)) {
        std::cerr << "Failed to set master volume. Error code: 0x" << std::hex << hr << std::endl;
        pVolume->Release();  // Release the volume object
        CoUninitialize();
        return -1;
    }

    std::cout << "Volume set to 50%." << std::endl;

    // Clean up
    pVolume->Release();
    CoUninitialize();

    return 0;
}
