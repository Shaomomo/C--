//---------------------------------------------------------------------------

#ifndef CibleH
#define CibleH


#include <iostream>
#include <string>
#include "SNImage.h"


class Cible : public SNImage
{
	private:
		int position_x_centre;
		int position_y_centre;
	public:
		Cible();
		int calcul_bord_cible();
		int calcul_diametre();
		int calcul_centre();
		void recadrage();
		void detection_zone();
		void detection_coloration();
		void detection_coloration_zone_180();
		int calcul_impact();
		int calcul_score();
		void affichage_score();






};


//---------------------------------------------------------------------------
#endif
