#include <a_samp>
#include <shoutcast>

#define SHOUTCAST_IP	"127.0.0.1"
#define SHOUTCAST_PORT	8000

new bool:songtoggle[MAX_PLAYERS char];

public OnFilterScriptInit()
{
	print("\n--------------------------------------");
	print(" Shoutcast");
	print("--------------------------------------\n");

	ShoutcastInit(SHOUTCAST_IP,SHOUTCAST_PORT);
	return 1;
}

public OnFilterScriptExit()
{
	ShoutcastExit();
	return 1;
}

public OnPlayerConnect(playerid)
{
	songtoggle[playerid] = false;
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	songtoggle[playerid] = false;
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/radio", true))
	{
		if(!IsValidStream()) return SendClientMessage(playerid, -1, "Stream is offline.");
		new string[64];
		if(songtoggle[playerid])
			StopAudioStreamForPlayer(playerid);
		else
		{
			format(string, sizeof(string), "http://%s:%i/listen.pls", SHOUTCAST_IP, SHOUTCAST_PORT);
			PlayAudioStreamForPlayer(playerid, string);
		}
		songtoggle[playerid] = !songtoggle[playerid];
		return 1;
	}
	return 0;
}

public OnRconCommand(cmd[])
{
	if(!strcmp(cmd, "stats", true))
	{
		printf("stream: http://%s:%i/listen.pls", SHOUTCAST_IP, SHOUTCAST_PORT);
		printf("current listeners: %i/%i", GetCurrentListeners(), GetMaxListeners());
		printf("peak listeners: %i", GetPeakListeners());
		printf("current song: %s", GetCurrentSong());
		printf("uptime: %i seconds", GetShoutcastUptime());	
	}
	return 1;
}

public OnSongChange(new_song[])
{
	new string[128];
	format(string,sizeof(string),"{0049FF}[Now playing] {00c9ff}%s - Listen with /radio",new_song);
	SendClientMessageToAll(-1, string);
	return 1;
}

public OnStreamStatusChange(bool:status)
{
	printf("Stream is now %s", status ? ("online") : ("offline"));
	return 1;
}
