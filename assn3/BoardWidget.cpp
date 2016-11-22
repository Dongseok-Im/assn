#pragma once
#include "BoardWidget.h"

void CurrentWidget::SetCurrentP(Board* BoardGame,int &randomindex)
{
	CurrentP=BoardGame->Getp(randomindex);	

	if (CurrentP->GetId() == 0)
	{
		while (1)
		{
			if (randomindex <= 2)
				randomindex += 1;

			else if (randomindex == 3)
				randomindex = 0;

			CurrentP = BoardGame->Getp(randomindex);

			if (CurrentP->GetId() != 0)
				break;

		}
	}




}
