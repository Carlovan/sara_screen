#ifndef _SARA_WIFI
#define _SARA_WIFI

// Connects to WiFi; uses saved credntials if present,
// or SmartConfig if either the credentials are not presents or
// checkPin is specified and it's HIGH
void connect(int checkPin = 0);

#endif
