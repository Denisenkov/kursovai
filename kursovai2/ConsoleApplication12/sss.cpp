#include "sss.h"
bool InstallationShipOnField(Field &a, int PositionOnField, Ship& Korabl) {
	int c, z = 0;
	c = rand() % 4;
	z = a.InstallationShipOnField(PositionOnField, c, Korabl);
	if (z == 0) {
		for (int l = 0; l < 4; l++) {

			if (z == 0)z = a.InstallationShipOnField(PositionOnField, l, Korabl);



		}
	}
	
	return z;
}
void RandomPlacementOfShips(Field &a) {
	srand(time(0));
	int  z = 0, PositionOnField;
	for (int j = 0; j < a.KorablAmount(); j++) {			
			z = 0;
			while (z == 0) {
				PositionOnField = rand() % (a.FieldSize() * a.FieldSize());
				if (!a.DoesShipExist(PositionOnField / a.FieldSize() + 1, PositionOnField % a.FieldSize() + 1)) {					
					z = InstallationShipOnField(a, PositionOnField, a.OutShip(j));
				}
			}
	}
	
};


void CoutField(Field &a) {
	char z;
	cout << "\n";
	cout << "    ";
	for (int i = 0; i < a.FieldSize(); i++) {
		z = 'А' + i;
		cout << z << " ";

	}
	cout << "\n\n";
	for (int i = 1; i < a.FieldSize() + 1; i++) {
		cout << setw(2) << i << "  ";
		for (int j = 1; j < a.FieldSize() + 1; j++) {

			if (a.DoesShipExist(i, j) && a.bIsCellFired(i, j)) { z = '+'; }
			else { if (a.bIsCellFired(i, j)) { z = '*'; } else { z = ' '; } }
			cout << z << setw(2);
		}
		cout << "\n";
	}

};
void CoutHint(Field &a) {
	char z;
	cout << "\n";
	cout << "    ";
	for (int i = 0; i < a.FieldSize(); i++) {
		z = 'А' + i;
		cout << z << " ";

	}

	cout << "\n\n";
	for (int i = 1; i < a.FieldSize() + 1; i++) {
		cout << setw(2) << i << "  ";
		for (int j = 1; j < a.FieldSize() + 1; j++) {

			if (a.DoesShipExist(i, j)) { z = 127; }
			else { z = ' '; }
			cout << z << setw(2);
		}
		cout << "\n";
	}
};
void vShootingAtCoordinates(Field &a, int x, int y) {
	int i;
	i = a.iShootingAtCoordinates(x, y);
	switch (i) {
	case 0: {
		cout << "Промах!\n";
		break;
	}
	case 1: {
		cout << "Ранен!\n";
		break;
	}
	case 2: {
		cout << "Убит!\n";
		break;
	}

	}

}
void NuclearStrike(Field &a) {
	for (int i = 1; i < a.FieldSize() + 1; i++) {
		for (int j = 1; j < a.FieldSize() + 1; j++) {

			a.iShootingAtCoordinates(i, j);
		}
	}
}
int AnalysisIn(Field &a,string c) {
	int z=0,d=0,h=0, x=0, y=0, t = a.FieldSize(),n=c.size();
	for (int i = n - 1; i > 0; i--) {
		if (c[i] >= 48 && c[i] <= 57) { x = x + (c[i] - 48) * pow(10, n - 1 - i); }
		else { d = 2; }
	}
	if ((x>t)||(x<=0)) { d=2; }
	if (-64 <= c[0] && c[0] < -64 + t) {
		y = c[0] + 65;
	}
	else { h = 2; }
	if (d != 2 && h != 2) {
		z=a.bIsCellFired(x, y);
	}
	else { z = 2; }
	if (z == 0) { vShootingAtCoordinates(a, x, y); }

	return z;
}
void cinShotCoordinates(Field &a) {
	cout << "Введите координаты удара (например: Г5)\n";
	bool t = 1;
	while (t) {	
		string x;
		cin >> x;
		cin.clear();
		while ((getchar()) != '\n');
		if (x == "ЯУ") {
			NuclearStrike(a); 
			t = 0;
		}
		else {
			switch (AnalysisIn(a,x)) {
			case 0: {
				t = 0;
				break;
			}
			case 1: {
				cout << "Этот квадрат уже разведан!\n";
				break;
			}
			case 2: {
				cout << "Неверный ввод!\n";
				break;
			}
			}
		}
	}
}

void Game() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Field a = 10;
	RandomPlacementOfShips(a);
	CoutHint(a);
	while (a.AreThereLivingShips()) {
		CoutField(a);
		cinShotCoordinates(a);		
	}
	CoutField(a);
	cout << "Мы победили!\n";

}

