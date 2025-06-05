#include "IC_textStructs.h"

#include "IC_globalVariables.h"
#include "IC_game.h"

std::string IC_text::str()
{
	if (stringPointer == nullptr || game->GetLocalisationSystem()->GetGeneration() != gen)
	{
		if (game->GetLocalisationSystem()->GetLocalised(identifier, stringPointer))
		{
			gen = game->GetLocalisationSystem()->GetGeneration();
		}
		else
		{
			stringPointer = nullptr;
			return "id_" + identifier; // No value found so just returning the identifier
		}
	}
	return *stringPointer;
}
