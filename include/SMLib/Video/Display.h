//-------------------------- File Display.h -----------------------------------
#ifndef SML_DISPLAY_H_
#define SML_DISPLAY_H_

//-----------------------------------------------------------------------------
//
// TODO Documentation: main title for file
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------
#include <SMLib/Video/Export.h>
#include <SMLib/Video/GeneralTypes.h>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// A main library namespace
//-----------------------------------------------------------------------------
namespace sml {
//-----------------------------------------------------------------------------
// A opened video module namespace
//-----------------------------------------------------------------------------
namespace video {

class VideoMode;

namespace cls { class DisplayImpl; }


class SML_VIDEO_API Display
{

public:

  //---------------------------------------------------------------------------
  // A destructor
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------
  ~Display() = default;

  //---------------------------------------------------------------------------
  // Returning a supported video modes list
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------
  std::vector<VideoMode> GetListVideoModes() const;

  //---------------------------------------------------------------------------
  // Doing request to the operating system
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------
  VideoMode GetVideoMode() const;

  //---------------------------------------------------------------------------
  // Setting up a custom mode for this display
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------
  bool SetVideoMode(const VideoMode& videoMode,
                    uint32_t flags = SML_VM_FULLSCREEN) const;

  //---------------------------------------------------------------------------
  // Checking a selected mode
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------
  bool IsValidMode(const VideoMode& videoMode) const;

  //---------------------------------------------------------------------------
  // Returning "true" if display is priamry
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------
  bool IsPrimary() const;

  //---------------------------------------------------------------------------
  // Getting a adapters fiendly description
  //---------------------------------------------------------------------------
  std::string GetAdapterDescription() const;

  //---------------------------------------------------------------------------
  // Getting a monitors fiendly description
  //---------------------------------------------------------------------------
  std::string GetMonitorDescription() const;

 protected: 

  friend class cls::DisplayImpl;
  friend class DisplayContainer;

  //---------------------------------------------------------------------------
  // Base constructor
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------
  Display(const std::string& name,
          const std::string& adapterDescription,
          const std::string& monitorDescription,
          const bool isPrimary);


private:

  //---------------------------------------------------------------------------
  // Member fields
  //
  // TODO: Documentations
  //
  //---------------------------------------------------------------------------

  std::string name_;
  std::string adapterDescription_;
  std::string monitorDescription_;
  bool isPrimary_;

};

} // namspace video
} // namspace sml
#endif // !SML_DISPLAY_H_
//---------------------- End of file Display.h --------------------------------
