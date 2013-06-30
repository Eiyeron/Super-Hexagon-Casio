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
			if(tmp1->nxt->d <= 0)
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

void update(Wall *list, unsigned int delta_time)
{
	Wall *tmp;
	tmp = list;

	do{
		if(tmp != NULL)
		{
			//just reducing the distance from the center
			tmp->d-=1;
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
void show(Wall *list, Camera *cam)
{
	/*

	0________________1
	/        0       \
  3/                  \1
  /                    \
3/______________________\2
 			2

 	*/
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
				int x[4];
				int y[4];
				float slopes[4];
				int i = 0;
				int j = 0;

					int tmpInt = 0;
					int x1=0, x2 = 0;
					//finding the two active edges
					int leftDotIndex = 0, rightDotIndex = 0, leftSlope=0, rightSlope=0;

				x[0]=tmp->d * cos1 + 64;
				x[1]=tmp->d * cos2 + 64;
				x[2]= (tmp->h + tmp->d) * cos2 + 64;
				x[3]=(tmp->h + tmp->d) * cos1 + 64;

				y[0]=tmp->d * sin1 + 32;
				y[1]=tmp->d * sin2 + 32;
				y[2]= (tmp->h + tmp->d) * sin2 + 32;
				y[3]=(tmp->h + tmp->d) * sin1 + 32;

				/*slopes[0] = (y[1] - y[0])/(x[1]-x[0]);
				slopes[1] = (y[2] - y[1])/(x[2]-x[1]);
				slopes[2] = (y[3] - y[2])/(x[3]-x[2]);
				slopes[3] = (y[0] - y[3])/(x[0]-x[3]);*/
				/*for(i = 0; i < tmp->h; i+=0.5)
				{
					ML_line((tmp->d + i) * cos2 + 64, (tmp->d + i) * sin2 + 32, (tmp->d + i) * cos1 + 64, (tmp->d + i) * sin1 + 32, BLACK);
				}*/


/*					i = y[0];
					j = y[0];

					for(i = 0; i < 4; i++)
						if(y[tmpInt] > y[i])
							tmpInt = i;
					i = tmpInt;
					tmpInt = 0;
					for(j = 0; j < 4; j++)
						if(y[tmpInt] < y[j])
							tmpInt = j;
					j = tmpInt;
					x1 = x[i];
					x2 = x[i];

					//i contains an index to the highest vertex and j the lowest
					tmpInt = 0;
					for(leftDotIndex = 0; leftDotIndex < 4; leftDotIndex ++)
					{
						if(leftDotIndex != i && leftDotIndex != j && (tmpInt == 0 || tmpInt > x[leftDotIndex]))
							tmpInt = x[leftDotIndex];
					}
					for(rightDotIndex = 0; rightDotIndex == i || rightDotIndex == j || rightDotIndex == leftDotIndex; rightDotIndex ++)
					{}						
					
					tmpInt = i;
					while(i <= j)
					{
						//getting the active slopes' indexes
						if(y[i] < y[leftDotIndex])
							leftSlope = getSlopeIndex(i, leftDotIndex);
						else leftSlope = getSlopeIndex(leftDotIndex, j);
						if(y[i] < y[rightDotIndex])
							rightSlope = getSlopeIndex(i, rightDotIndex);
						else rightSlope = getSlopeIndex(rightDotIndex, j);

						ML_horizontal_line(y[tmpInt] + i, x1, x2, BLACK);
						ML_horizontal_line(y[tmpInt] + i, x2, x1, BLACK);
						x1 = x1 - (1/slopes[leftSlope]);
						x2 = x2 - (1/slopes[rightSlope]);
						i++;
					}*/
				ML_filled_polygone(x, y, 4, BLACK);
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
