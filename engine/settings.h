#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <argp.h>
#include <argz.h>

//create struct for setting to be populated and passed back

struct SETTINGS_DATA
{
  int screenWidth,screenHeight;
  std::string *windowName,*plyName;
};

class SETTINGS
{
public:
  SETTINGS();
  struct SETTINGS_DATA currentSettings();
  void parseSettingsFile(std::string);
  void parseCommandLine(int,char**);
private:
  static struct SETTINGS_DATA Statsettings;
  static int parse_opt(int, char*, struct argp_state*);
  int argc;
  char **argv;

};

static SETTINGS gamesettings;

#endif
