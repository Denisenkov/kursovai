#ifndef SSS_H
#define SSS_H
#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
using namespace std;
class Ship {
private:
	int LifeShip;
	bool ExistenceShip;
	bool Stroke = 0;
public:
	Ship() {
		LifeShip = 0;
		ExistenceShip = 0;
	}
	Ship(int i) {
		LifeShip = i;
		ExistenceShip = i;
	}
	Ship(const Ship&d) {
		LifeShip = d.LifeShip;
		ExistenceShip = d.ExistenceShip;
	}
	bool DoesShipExist() {
		return ExistenceShip;
	}
	int IsShipAlive() {
		return LifeShip;
	}
	void ShipDamage() {
		LifeShip = LifeShip - 1;
		if (LifeShip < 0)LifeShip = 0;
	}
	void vStroke() {
		Stroke=1;
	}
	bool bStroke() {
		return Stroke;
	}
	void CreatShip(int i) {
		LifeShip = i;
		ExistenceShip = i;
	}

};

class Cell {
private:
	bool IsCellFired;
	Ship* Korabl;
public:
	Cell() {
		Ship x=0;
		IsCellFired = 0;
		Korabl = &x;	
	}
	Cell(const Cell&d) {
		IsCellFired = d.IsCellFired;
		Korabl = d.Korabl;
		
	}
	~Cell() {
				
	}
	void InstallationShipOnField(Ship &x) {
		Korabl = &x;
		
	}
	bool DoesShipExist() {		
		return Korabl->DoesShipExist();
	}
	int IsShipAlive() {
		return Korabl->IsShipAlive();
	}
	bool bIsCellFired() {
		return IsCellFired;
	}
	void vIsCellFired() {
		IsCellFired = 1;
	}
	void ShipDamage() {
		Korabl->ShipDamage();
	}
	void vStroke() {
		Korabl->vStroke();
	}
	bool bStroke() {
		return Korabl->bStroke();
	}
	Ship& OutShip()  {
		return *Korabl;
	}
	
};
class Field {
private:
	Cell** ArrCell;
	Ship* ArrKorabl;
	Ship KorablNull;
	
	int SizeField;
	int AmountKorabl;
	int MaxSizeKoradl;
	int InstallationShipOnField( int PositionOnField,  int Route1, int Route2,Ship &Korabl) {
		int z = 0, x = 0;
		
		for (int l = 0; l < Korabl.IsShipAlive(); l++) {
			for (int r = 0; r < 9; r++) {
				if (ArrCell[PositionOnField / SizeField + l * Route1 + r / 3][PositionOnField % SizeField + l * Route2 + r % 3].DoesShipExist()) { x = 1;  }

			}
		}
		if (x == 0) {
			for (int l = 0; l < Korabl.IsShipAlive(); l++) {
				ArrCell[PositionOnField / SizeField + 1 + l * Route1][PositionOnField % SizeField + 1 + l * Route2].InstallationShipOnField(Korabl);			
			}
			z = 1;
		}
		return z;
	};	
public:
	Field(int ii) {
		SizeField = ii;
		AmountKorabl = 0;
		MaxSizeKoradl = 0;
		int x = 0;
		
		
		while (x+MaxSizeKoradl < ii * ii) {
			MaxSizeKoradl = MaxSizeKoradl + 1;
			AmountKorabl = AmountKorabl + MaxSizeKoradl;
			for (int j = MaxSizeKoradl; j >= 1;j--) {
				x = x + (j + 2) * 3;
			}
		}
		ArrKorabl = new Ship[AmountKorabl];
		x = 0;
		for (int j = MaxSizeKoradl; j >= 1; j--) {
			for (int i = 0; i<=MaxSizeKoradl-j; i++) {
				ArrKorabl[x].CreatShip(j);
			    x = x + 1;
			}
		}
			
		ArrCell = new  Cell * [SizeField + 2];
		for (int i = 0; i < SizeField+2; i++) {
			
			ArrCell[i] = new Cell[SizeField + 2];
			
		}
		
		for (int i = 0; i < SizeField + 2; i++) {
			for (int j = 0; j < SizeField + 2; j++) {
				ArrCell[i][j].InstallationShipOnField(KorablNull);				
			}
		}
		
	}	
	~Field() {
		delete[] ArrKorabl;


		for (int i = 0; i < SizeField + 2; i++) {

			delete[] ArrCell[i];

		}
		delete[]ArrCell;

	}
	bool InstallationShipOnField(int PositionOnField, int Route, Ship& Korabl) {
		int z = 0;

		if (Route == 0) {
			if (PositionOnField / SizeField - Korabl.IsShipAlive() + 1 >= 0) {
				z = InstallationShipOnField( PositionOnField,-1, 0 , Korabl );
			}
		}
		if (Route == 1) {
			if (PositionOnField / SizeField + Korabl.IsShipAlive() - 1 < SizeField) {
				z = InstallationShipOnField( PositionOnField,1, 0 , Korabl );
			}
		}
		if (Route == 2) {
			if (PositionOnField % SizeField - Korabl.IsShipAlive() + 1 >= 0) {
				z = InstallationShipOnField( PositionOnField,  0, -1, Korabl);
			}
		}
		if (Route == 3) {
			if (PositionOnField % SizeField + Korabl.IsShipAlive() - 1 < SizeField) {
				z = InstallationShipOnField( PositionOnField, 0, 1, Korabl );
			}
		}
		
		return z;

	};
	void CircleDestroyedShip() {
		bool b;
		for (int i = 1; i < SizeField + 1; i++) {
			for (int j = 1; j < SizeField + 1; j++) {
				b = ArrCell[i][j].IsShipAlive();
				if (!b&&ArrCell[i][j].DoesShipExist()&& !ArrCell[i][j].bStroke()) {					
					for (int r = 0; r < 9; r++) {
						ArrCell[i-1+r%3][j-1+r/3].vIsCellFired();
					}
				}
			}
		}
		for (int j = 0; j < AmountKorabl; j++) {
			if(!ArrKorabl[j].IsShipAlive())ArrKorabl[j].vStroke();
		}
	}
	int iShootingAtCoordinates( int x, int y) {
		int i=0;
		ArrCell[x][y].ShipDamage();
		ArrCell[x][y].vIsCellFired();
		if (ArrCell[x][y].DoesShipExist()) if (ArrCell[x][y].IsShipAlive()) { i = 1; }
		else { i = 2; 
		CircleDestroyedShip();
		}
		return i;
	}
	bool AreThereLivingShips() {
		bool b = 0;
		for (int i = 0; i < AmountKorabl; i++) {
			if (ArrKorabl[i].IsShipAlive()) {
				b = 1;
			}
		}
		return b;
	}
	Ship& OutShip(int i) const {
		return (ArrKorabl[i]);
	}
	bool bIsCellFired(int x, int y)const {
		return ArrCell[x][y].bIsCellFired();
	}
	bool DoesShipExist(int x,int y)const {
		
		return ArrCell[x][y].DoesShipExist();
	}
	int FieldSize() const {
		return SizeField;
	}
	int KorablAmount() {
		return AmountKorabl;
	}
	int KoradlMaxSize() {
		return MaxSizeKoradl;
	}
};

bool InstallationShipOnField(Field &a, int PositionOnField, Ship& Korabl);

void RandomPlacementOfShips(Field &a);

void CoutField(Field &a);
void CoutHint(Field &a);

int AnalysisIn(Field &a,string x);

void vShootingAtCoordinates(Field &a, int x, int y);
void NuclearStrike(Field &a);
void cinShotCoordinates(Field& a);

void Game();

#endif

