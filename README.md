# SAMP-Shoutcast

<h1>Information</h1>
This is an include to use if u have a shoutcast server. When you have a shoutcast server people can play as "DJ" by streaming songs to the shoutcast server; And this include takes care of the transitions between songs and the stream information.

The shoutcast.pwn is a demo

<h1>Dependencies</h1>
To order to get this include to work you need 1 plugin: 
* <a href="https://github.com/Hual/SAMPSON">SAMPSON</a>

<h1>Config</h1>
```PAWN
#define SHOUTCAST_IP	  "127.0.0.1" //IP of the shoutcast server
#define SHOUTCAST_PORT	8000        //port of the shoutcast server
```

Only these 2 things are required to run the include.

<h1>Media</h1>
The rcon command "stats" returns this for example:

<img src="http://puu.sh/l0I6h.png" />
