//---------------------- File DisplayImpl.cpp----------------------------------

#include "..\DisplayImpl.h"

#include <windows.h>

//-----------------------------------------------------------------------------
// A main library namespace
//-----------------------------------------------------------------------------
namespace sml {

//-----------------------------------------------------------------------------
// A opened video module namespace
//-----------------------------------------------------------------------------
namespace video {

//-----------------------------------------------------------------------------
// A closed video module namespace
//-----------------------------------------------------------------------------
namespace cls {

//-----------------------------------------------------------------------------
// Returning an active display instance
//-----------------------------------------------------------------------------
std::vector<PDisplay>
DisplayImpl::GetDisplayList()
{
  DISPLAY_DEVICE di; // Display Inforamtion
  ZeroMemory(&di, sizeof(di));
  di.cb = sizeof(di);

  std::string deviceName;
  std::string deviceString;
  std::string monitorDesc;
  bool isPrimary = false;

  std::vector<PDisplay> displays;

  for ( size_t i = 0; EnumDisplayDevices(NULL, i, &di, 0); i++) 
  {
    if (di.StateFlags & DISPLAY_DEVICE_ACTIVE) {

      deviceName = di.DeviceName;
      deviceString = di.DeviceString;
      isPrimary = (di.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE);

      ZeroMemory(&di, sizeof(di));
      di.cb = sizeof(di);

      if (EnumDisplayDevices(deviceName.c_str(), 0, &di, 0)) {
        monitorDesc = di.DeviceString;
      }
      
      displays.emplace_back(
        std::make_shared<Display>(Display(deviceName,
                                          deviceString,
                                          monitorDesc,
                                          isPrimary))); 
    }
  }

  return displays;

}

//-----------------------------------------------------------------------------
// Returning a vector of supported modes for display
//-----------------------------------------------------------------------------
std::vector<VideoMode>
DisplayImpl::GetListVideoModes(const char* displayName)
{
  std::vector<VideoMode> modes;
  DEVMODE md;
  ZeroMemory(&md, sizeof(md));

  for (size_t i = 0; EnumDisplaySettings(displayName, i, &md); i++) {

    VideoMode mode(md.dmPelsWidth, 
                   md.dmPelsHeight, 
                   md.dmBitsPerPel,
                   md.dmDisplayFrequency);

    if (std::find(modes.begin(), modes.end(), mode) == modes.end()) {

      modes.push_back(mode);

    }
  }

  return modes;
}

//-----------------------------------------------------------------------------
// Returning a current desktop mode for selected display
//-----------------------------------------------------------------------------
VideoMode
DisplayImpl::GetVideoMode(const char* displayName)
{
  DEVMODE md;
  ZeroMemory(&md, sizeof(md));

  EnumDisplaySettings(displayName, ENUM_CURRENT_SETTINGS, &md);

  return VideoMode(md.dmPelsWidth,
                   md.dmPelsHeight,
                   md.dmBitsPerPel,
                   md.dmDisplayFrequency);
}

//-----------------------------------------------------------------------------
// Seting a video mode to a selected display
//-----------------------------------------------------------------------------
bool
DisplayImpl::SetVideoMode(const char* displayName,
                          const VideoMode& mode,
                          uint32_t flags)
{
  DEVMODE dm;
  ZeroMemory(&dm, sizeof(dm));
  dm.dmSize = sizeof(dm);
  bool success = EnumDisplaySettings(displayName, ENUM_CURRENT_SETTINGS, &dm);
  if (!success)
    return false;

  dm.dmPelsWidth = mode.width;
  dm.dmPelsHeight = mode.height;
  dm.dmBitsPerPel = mode.bitPerPixel;
  dm.dmDisplayFrequency = mode.displayFrecency;
  dm.dmFields =
    (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY);

  // DISP_CHANGE_DUCCESSFUL expanding into 0
  return (ChangeDisplaySettingsEx(displayName, &dm, NULL, flags, 0) == 0);
}

} // namespace cls
} // namespace video
} // namespace sml

//------------------- End of file DisplayImpl.cpp -----------------------------
