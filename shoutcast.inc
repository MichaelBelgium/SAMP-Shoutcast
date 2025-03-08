#include <a_samp>
#include <a_json>
#include <a_http>

/*
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
*/

forward OnResponse(index, response_code, data[]);
forward OnUpdate();
forward OnSongChange(new_song[]);
forward OnStreamStatusChange(bool:status);

enum shData
{
    Timer,
    IP[16],
    Port,
    bool:Status,
    CurrentSong[256],
    Listeners,
    PeakListeners,
    StreamUptime,
    MaxListeners,
}

new Shoutcast[shData];

ShoutcastInit(ip_address[],port)
{
    Shoutcast[Timer] = SetTimer("OnUpdate", 5000, true);
    Shoutcast[Status] = false;
    Shoutcast[Port] = port;

    format(Shoutcast[IP], 16, "%s", ip_address);
}

public OnResponse(index, response_code, data[])
{
    if(response_code == 200)
    {
        new JSONNode:response = json_parse_string(data);

        new bool:newStatus = json_get_bool(response, "streamstatus");
        Shoutcast[Listeners] = json_get_int(response, "currentlisteners");
        Shoutcast[PeakListeners] = json_get_int(response, "peaklisteners");
        Shoutcast[StreamUptime] = json_get_int(response, "streamuptime");
        Shoutcast[MaxListeners] = json_get_int(response, "maxlisteners");

        if(Shoutcast[Status])
        {
            new newSong[256];
            json_get_string(response, newSong, sizeof(newSong), "songtitle");

            if(strcmp(Shoutcast[CurrentSong], newSong, true) != 0)
            {
                CallLocalFunction("OnSongChange", "s", newSong);
                Shoutcast[CurrentSong] = newSong;
            }
        }

        json_close(response);

        if(Shoutcast[Status] != newStatus)
        {
            CallLocalFunction("OnStreamStatusChange", "d", newStatus);
            Shoutcast[Status] = newStatus;
        }
    }
    else
        printf("ERROR Onresponse: %i", response_code);
}

public OnUpdate()
{
    new endpoint[128];
    format(endpoint,sizeof(endpoint),"%s:%i/stats?sid=1&json=1",Shoutcast[IP],Shoutcast[Port]);
    HTTP(0, HTTP_GET, endpoint, "", "OnResponse");

    return 1;
}


ShoutcastExit()
{
    KillTimer(Shoutcast[Timer]);
}

stock IsValidStream() 		return Shoutcast[Status];
stock GetCurrentSong() 		return Shoutcast[CurrentSong];
stock GetCurrentListeners() return Shoutcast[Listeners];
stock GetPeakListeners() 	return Shoutcast[PeakListeners];
stock GetShoutcastUptime() 	return Shoutcast[StreamUptime];
stock GetMaxListeners() 	return Shoutcast[MaxListeners];

