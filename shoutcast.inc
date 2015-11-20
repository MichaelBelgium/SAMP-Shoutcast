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

new gTmp[256], JSONNode:node, gTimer = -1, song[2][64], bool:g_status;
new g_IP[16], g_port;

ShoutcastInit(ip_address[],port)
{
	gTimer = SetTimer("OnUpdate", 5000, true);

	song[0] = "N/A";
	format(g_IP, sizeof(g_IP),"%s",ip_address);
	g_port = port;
}

public OnResponse(index, response_code, data[])
{
	if(response_code == 200)
	{
		node = json_parse_string(data);

		if(IsValidStream())
			format(song[1],64,"%s",GetData("songtitle"));
	}
	else
		printf("ERROR Onresponse: %i", response_code);
}

public OnUpdate()
{
	if(gTimer == -1) return 0;
	format(gTmp,sizeof(gTmp),"%s:%i/stats?sid=1&json=1",g_IP,g_port);
	HTTP(0, HTTP_GET, gTmp, "", "OnResponse");

	if(strcmp(song[0], song[1], true) != 0)
	{
		CallLocalFunction("OnSongChange", "s", song[1]);
		song[0] = song[1];
	}

	if(g_status != (IsValidStream() == 1) ? true : false)
	{
		CallLocalFunction("OnStreamStatusChange", "d", IsValidStream());
		g_status = (IsValidStream() == 1) ? true : false;
	}
	return 1;
}

stock GetData(data[])
{
	json_get_string(node, gTmp, sizeof(gTmp), data);
	if(gTmp[0] == EOS) gTmp = "N/A";
	return gTmp;
}

ShoutcastExit()
{
	json_close(node);
	KillTimer(gTimer);
	gTimer = -1;
}

stock IsValidStream() 		return json_get_bool(node, "streamstatus");
stock GetCurrentSong() 		return song[0];
stock GetCurrentListeners() return json_get_int(node,"currentlisteners");
stock GetPeakListeners() 	return json_get_int(node,"peaklisteners");
stock GetShoutcastUptime() 	return json_get_int(node,"streamuptime");
stock GetMaxListeners() 	return json_get_int(node,"maxlisteners");

