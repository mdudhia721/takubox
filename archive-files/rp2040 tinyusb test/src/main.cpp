#include <Adafruit_TinyUSB.h>
#include <MPG.h>
#include <XInput.h>

/* This sketch demonstrates USB HID gamepad use.
 * This sketch is only valid on boards which have native USB support
 * and compatibility with Adafruit TinyUSB library. 
 * For example SAMD21, SAMD51, nRF52840.
 * 
 * Make sure you select the TinyUSB USB stack if you have a SAMD board.
 * You can test the gamepad on a Windows system by pressing WIN+R, writing Joy.cpl and pressing Enter.
 */

// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_GAMEPAD()
};

// USB HID object
Adafruit_USBD_HID usb_hid;

// Report payload defined in src/class/hid/hid.h
// - For Gamepad Button Bit Mask see  hid_gamepad_button_bm_t
// - For Gamepad Hat    Bit Mask see  hid_gamepad_hat_t
hid_gamepad_report_t gp;

void setup() {
  // Manual begin() is required on core without built-in support e.g. mbed rp2040
    if (!TinyUSBDevice.isInitialized()) {
        TinyUSBDevice.begin(0);
    }

    Serial.begin(115200);

    // Setup HID
    usb_hid.setPollInterval(2);
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.begin();

  // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
    if (TinyUSBDevice.mounted()) {
        TinyUSBDevice.detach();
        delay(10);
        TinyUSBDevice.attach();
    }

    Serial.println("Adafruit TinyUSB HID Gamepad example");
}

void loop() {
    #ifdef TINYUSB_NEED_POLLING_TASK
        // Manual call tud_task since it isn't called by Core's background
        TinyUSBDevice.task();
    #endif

  // not enumerated()/mounted() yet: nothing to do
    if (!TinyUSBDevice.mounted()) {
        return;
    }

    if (!usb_hid.ready()) return;

    // Random touch
    Serial.println("Random touch");
    gp.x = random(-127, 128);
    gp.y = random(-127, 128);
    gp.hat = random(0, 9);
    gp.buttons = random(0, 0xffff);
    usb_hid.sendReport(0, &gp, sizeof(gp));
    delay(2000);

  // */
}