#include "IC_visualDebugger.h"

IC_visualDebugger::IC_visualDebugger()
{
	debugStrings = std::vector<IC_debugString>();
}

void IC_visualDebugger::AddDebugString(const IC_debugString& DebugString, bool Log)
{
	if (Log)
	{
		printf(DebugString.str.c_str());
		printf("\n");
	}

	debugStrings.insert(debugStrings.begin(), DebugString);
	if (debugStrings.size() > 250)
	{
		debugStrings.pop_back();
	}
}

void IC_visualDebugger::DrawDebugStrings()
{
	std::vector<IC_debugString> newDebugStrings = std::vector<IC_debugString>();

	for (int i = 0; i < debugStrings.size(); i++)
	{
		if (debugStrings[i].duration == 0.0f)
		{
			DrawText(debugStrings[i].str.c_str(), 10, 10 + i * 20, 20, debugStrings[i].color);
		}
		else if (GetTime() - debugStrings[i].creationTime <= debugStrings[i].duration)
		{
			DrawText(debugStrings[i].str.c_str(), 10, 10 + i * 20, 20, debugStrings[i].color);
			newDebugStrings.push_back(debugStrings[i]);
		}
	}
	debugStrings = newDebugStrings;
}