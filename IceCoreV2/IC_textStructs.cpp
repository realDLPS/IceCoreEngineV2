#include "IC_textStructs.h"

#include "IC_globalVariables.h"
#include "IC_game.h"

std::string IC_text::str()
{
	std::string out;
	if (game->GetLocalisationSystem()->GetLocalised(identifier, out))
	{
		return out;
	}
	// No localised value was found so returning the preview
	return preview;
}
