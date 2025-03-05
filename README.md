# SAMP-Shoutcast

## Information
This is an include to use if u have a shoutcast server. When you have a shoutcast server people can play as "DJ" by streaming songs to the shoutcast server; And this include takes care of the transitions between songs and the stream information.

The shoutcast.pwn is a demo

## Dependencies
To order to get this include to work you need 1 plugin: 
* [SAMPSON](https://github.com/Hual/SAMPSON)

## Config

```PAWN
#define SHOUTCAST_IP	"127.0.0.1" //IP of the shoutcast server
#define SHOUTCAST_PORT	8000        //port of the shoutcast server
```


## Functions and callbacks

```PAWN
native IsValidStream();
native GetCurrentSong();
native GetCurrentListeners();
native GetPeakListeners();
native GetShoutcastUptime()
native GetMaxListeners();

native ShoutcastInit(ip_address[],port);
native ShoutcastExit();
native OnSongChange(new_song[]);
native OnStreamStatusChange(bool:status);
```