#include "wall.h"
#include "fixed.h"

Wall *addWall(Wall *list, int d, int h, int id, int line)
{
	Wall *tmp;
	Wall *new;
	tmp = list;

	new = malloc(sizeof(Wall));
	if(new == NULL) {
		// Uh oh
		return list;
	}
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

	if(list == NULL) return list;
	if(list->d <= d)
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
			if(tmp1->nxt->d <= d)
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

void drawWalls(Wall *list, Camera *cam, int nb_lines, Line_Transition line_transition)
{//NEEDS A COMPLETE REWRITE TO SUPPORT THE LINE TRANSITIONS !
	Wall *tmp;

	fix coeff = 0;
	fix transition_angle = 0;
	fix delta_angle = fdiv(FIX(360), FIX(nb_lines));
	fix offset = 0;

	if(line_transition.delta_nb_lines == 1)
		nb_lines ++;

	if(line_transition.counter_start != 0)
		coeff = fdiv(FIX(line_transition.counter), FIX(line_transition.counter_start));
	transition_angle = fmul(delta_angle, coeff);

	offset = fdiv(fmul((delta_angle - transition_angle), FIX(line_transition.delta_nb_lines)), FIX(nb_lines));

	tmp = list;
	do{
		if(tmp != NULL)
		{
			if(tmp->d - tmp->h < 128)
			{
				const fix delta_angle_minus_offset = delta_angle - offset;
				const fix angle =  fmul(delta_angle_minus_offset, FIX(tmp->line)) + FIX(cam->angle);
				const fix cos1 = fcos(angle);
				const fix cos2 = fcos(angle + delta_angle_minus_offset);
				const fix sin1 = fsin(angle);
				const fix sin2 = fsin(angle + delta_angle_minus_offset);
				int i;

				fix dist = ftofix(tmp->d + cam->zoom);
				for(i = 0; i < tmp->h && dist > FIX(8); ++i) {
					if(dist < FIX(96))
					ML_line(64 + fixtof(fmul(dist, cos1)), 32 + fixtof(fmul(dist,sin1)), 64 + fixtof(fmul(dist, cos2)), 32 + fixtof(fmul(dist, sin2)), BLACK);
					dist -= FIX(1);
				}
			}
		}
		tmp = tmp->nxt;
	}while(tmp != NULL);

}

//tests every Wall in the list
bool isColliding(Wall *list, int player_angle, int nb_lines)
{
	Wall *tmp;
	tmp = list;

	do{
		if(tmp != NULL)
		{
			if(tmp-> d <= 8+tmp->h + 2)//if the wall is close enough from the center of the screen
			{	//and is on the same line than the player
				if(tmp->line == (int)(player_angle/ (360 / nb_lines)) && tmp->line < nb_lines)
				{	//BOOM
					return true;
				}
			}
		}
		tmp = tmp->nxt;
	}while(tmp != NULL);
	return false;
}
