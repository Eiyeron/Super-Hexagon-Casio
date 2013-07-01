#include "wall.h"

Wall *addWall(Wall *list, int d, int h, int id, int line)
{
	Wall *tmp;
	Wall *new;
	tmp = list;

	new = malloc(sizeof(Wall));
	new->d = d;
	new->h = h;
	new->id = id;
	new->line = line;
	new->nxt = NULL;

	if(list == NULL)
		return new;
	else if(list != NULL)
	{
		while (tmp->nxt != NULL){
			tmp = tmp->nxt;
		}
		tmp->nxt = new;
		return list;
	}

}

Wall *removeWall(Wall *list, int d)
{
	Wall *tmp1;
	Wall *tmp2;

	if(list->d <= 0)
	{
		if(list->nxt != NULL)
			tmp1 = list->nxt;
		else
			tmp1 = NULL;
		free(list);
		return tmp1;
	}
	tmp1 = list;
	do{
		if(tmp1->nxt != NULL)
		{
			if(tmp1->nxt->d <= 0.0)
			{
				tmp2 = tmp1->nxt;
				if(tmp1->nxt->nxt != NULL)
					tmp1->nxt = tmp1->nxt->nxt;
				else
					tmp1->nxt = NULL;
				free(tmp2);
			}
		}
		tmp1 = tmp1->nxt;
	}while(tmp1 != NULL);
	return list;
}

void updateWalls(Wall *list, unsigned int delta_time)
{
	//we want to move the obstacle by 1 every two ticks (1/64 seconds ~= 1/60)
	//
	Wall *tmp;
	tmp = list;

	do{
		if(tmp != NULL)
		{
			//just reducing the distance from the center
			tmp->d -= 0.5 * delta_time;
		}
		tmp = tmp->nxt;
	}while(tmp != NULL);
}

//these are the actual drawing functions
//they should the rewritten from scratch
int getSlopeIndex(int dot1, int dot2)
{
	if(dot2 - dot1 == 1)
	{
		return dot1;
	}else if(dot2 - dot1 == -1){
		return dot2;
	}else return 3;
}
void drawWalls(Wall *list, Camera *cam)
{
	Wall *tmp;
	tmp = list;
	do{
		if(tmp != NULL)
		{
			if(tmp->d + tmp->h< 64)
			{

				const float angle = PI * ((tmp->line)*60 +cam->angle) / 180;
				const float cos1 = cos(angle);
				const float cos2 = cos(angle + PI/3);
				const float sin1 = sin(angle);
				const float sin2 = sin(angle + PI/3);
				int i,j, x, y;
				float dist = tmp->d - tmp->h;
				for(i = 0; i < tmp->h; ++i) {
					if(dist <= 8) break;
					ML_line(64 + dist*cos1, 32 + dist*sin1, 64 + dist*cos2, 32 + dist*sin2, BLACK);
					--dist;
				}
			}
		}
		tmp = tmp->nxt;
	}while(tmp != NULL);
}

//tests every Wall in the list
bool isColliding(Wall *list, int player_angle)
{
	Wall *tmp;
	tmp = list;

	do{
		if(tmp != NULL)
		{
			if(tmp-> d <= 8)//if the wall is close enough from the center of the screen
			{	//and is on the same line than the player
				if(tmp->line == (int)(player_angle/60)) //&& tmp->line * 60 + 60 > player_angle)
				{	//BOOM
					return true;
				}
			}
		}
		tmp = tmp->nxt;
	}while(tmp != NULL);
	return false;
}
