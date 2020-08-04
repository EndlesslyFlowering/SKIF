#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <wtypes.h>
#include <steam/isteamuser.h>

class skValveDataFile
{
public:
  skValveDataFile (std::wstring source);

  static constexpr
    uint32_t _LastSteamApp = 0;

  struct appinfo_s
  {
       AppId_t appid;
      uint32_t size;
      uint32_t state;
    __time32_t last_update;
      uint64_t access_token;
       uint8_t sha1sum [20];
      uint32_t change_num;

    struct section_desc_s {
      void*  blob;
      size_t size;
    };

    struct section_s {
      enum _TokenOp  {
        SectionBegin = 0x0,
        String       = 0x1,
        Int32        = 0x2,
        Int64        = 0x7,
        SectionEnd   = 0x8
      };

      using _kv_pair =
        std::pair <const char*, std::pair <_TokenOp, void *>>;

      struct section_data_s {
        std::string            name;
        section_desc_s         desc;
        std::vector <_kv_pair> keys;
      };

      std::vector <
        section_data_s
      > finished_sections;

      void parse (section_desc_s& desc);
    };

    void*      getRootSection (size_t* pSize = nullptr);
    appinfo_s* getNextApp     (void);
  };

  appinfo_s* getAppInfo ( uint32_t     appid,
                          ISteamUser* pUser = nullptr );

  struct header_s
  {
    DWORD     version;
    DWORD     universe;
    appinfo_s head;
  };

  header_s*  base = nullptr;
  appinfo_s* root = nullptr;

protected:
private:
  std::wstring        path;
  std::vector <BYTE> _data;
};