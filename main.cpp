#include <iostream>
#include <spdlog/spdlog.h>

extern "C" {
#include <hidapi/hidapi.h>
}


static const uint16_t FRDM_FC_VENDOR_ID  = 0xFDFC;
static const uint16_t FRDM_FC_PRODUCT_ID = 0x0001;
auto                  console            = spdlog::stdout_logger_mt("frdm-fan-control", true);

static void LogInit() {
    spdlog::set_level(spdlog::level::debug);
    console->info("FRDM-Kxxx Fan Controller Interface v0.1");
}

static void HIDInit() {
    if (hid_init() < 0) {
        console->critical("hid_init() failed!");
        exit(-1);
    }
}

static hid_device *OpenControllerDevice() {
    console->info("Connecting to your fan controller...");
    auto info = hid_enumerate(FRDM_FC_VENDOR_ID, FRDM_FC_PRODUCT_ID);
    console->debug("opening device at path: {0}", info->path);
    auto dev = hid_open_path(info->path);
    if (dev == nullptr) {
        console->error("Couldn't open device.");
        exit(-1);
    }
}


static std::string GetProductName(hid_device *dev) {
    wchar_t wbuf[255];
    if (hid_get_product_string(dev, wbuf, 255) < 0) {
        console->warn("failed to get mfg name");
        return "ERR";
    }
    std::wstring uname_str(wbuf);
    return std::string(uname_str.begin(), uname_str.end());
}

static std::string GetManfacturerName(hid_device *dev) {
    wchar_t wbuf[255];
    if (hid_get_manufacturer_string(dev, wbuf, 255) < 0) {
        console->warn("failed to get mfg name");
        return "ERR";
    }
    std::wstring uname_str(wbuf);
    return std::string(uname_str.begin(), uname_str.end());
}

int main() {
    LogInit();
    HIDInit();
    auto controller = OpenControllerDevice();
    auto name = GetProductName(controller);
    console->info("Found '{0}'", name);
    return 0;
}