#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct zaznam{
	char meno_priezvisko[30];
	char pohlavie;
	int rok_narodenia;
	char SPZ[8];
	char priestupok;
	int pokuta;
	int datum_priestupku;
};
struct novy_zaznam{
	char name_surname[30];
	char pohlavie;
	int rok_narodenia;
	char SPZ[8];
	char priestupok;
	int pokuta;
	int datum_priestupku;
};

int pocet_zaznamov(FILE *f){
	int pocet = 0;
	char c;
	char x;
	int datum; 
	while((c = fgetc(f)) != EOF){
		if(c == '\n'){
			x = fgetc(f);
			if(x == '\n')
				pocet++;
		}
	}
	return pocet+1;
}

void ukonci(FILE *f){
	if (fclose(f) == EOF) {
		printf("Subor sa nepodarilo zatvorit\n");
	}
}

int main(){
	FILE *f;
	struct zaznam *pole = NULL;
	struct novy_zaznam *nove_pole = NULL;
	printf("start\n");
	char c;
	int pocet, datum, novy_pocet;

	scanf("%c", &c);
	while(c != 'k'){
		if(c == 'o'){
			if ((f = fopen("priestupky.txt", "r")) == NULL) {
				printf("Subor sa nepodarilo otvorit\n");
			}
			pocet = pocet_zaznamov(f);
			if(pole != NULL){
				free(pole);
				pole = NULL;
			}
			if((pole = (struct zaznam*)malloc((sizeof(struct zaznam))*pocet)) == NULL){
				printf("Pole nie je naplnene");
			}
			else{
				rewind(f);
			
				for(int i = 0; i < pocet; i++){
					fgets(pole[i].name_surname, 30, f);	
					fscanf(f," %c\n", &pole[i].pohlavie);					
					fscanf(f," %d\n", &pole[i].rok_narodenia);					
					fscanf(f," %s\n", pole[i].SPZ);					
					fscanf(f," %c\n", &pole[i].priestupok);					
					fscanf(f," %d\n", &pole[i].pokuta);
					fscanf(f," %d\n", &pole[i].datum_priestupku);
				}
			}			
		}
		else if(c == 'v'){
				if(pole != NULL){
					for(int i = 0; i < pocet; i++){
						printf("meno priezvisko: %s\n", pole[i].name_surname);
						printf("pohlavie: %c\n", pole[i].pohlavie);
						printf("rok narodenia: %d\n", pole[i].rok_narodenia);
						printf("SPZ: %s\n", pole[i].SPZ);
						printf("typ priestupku: %c\n", pole[i].priestupok);
						printf("vyska pokuty: %d\n", pole[i].pokuta);
						printf("datum priestupku: %d\n", pole[i].datum_priestupku);
						printf("\n");
					}
				}
			}
		else if(c == 'x'){
			if(pole != NULL){
				printf("aktualny datum: \n");
				scanf("%d", &datum);
				datum = datum/10000;

				for(int i = 0; i < pocet; i++){
					if(datum == (pole[i].datum_priestupku/10000) && pole[i].priestupok == '0'){
						printf("meno priezvisko: %s\n", pole[i].name_surname);
						printf("SPZ: %s\n", pole[i].SPZ);
						printf("datum priestupku: %d\n", pole[i].datum_priestupku);
						printf("\n");
					}	
				}
				
			}
		}
		else if(c == 'r'){
			if(pole != NULL){
				double odmena = 0;
				printf("Aktualny datum: \n");
				scanf("%d", &datum);
				datum = (datum/100)%100;
				for(int i = 0; i < pocet; i++){
					if(datum == (pole[i].datum_priestupku/100)%100){
						if(pole[i].priestupok == '1'){
							odmena = odmena + (pole[i].pokuta*0.052);
						}
						else if(pole[i].priestupok == '0'){
							odmena = odmena + (pole[i].pokuta*0.038);
						}
					}
				}
				if(odmena > 0)
					printf("%.2lf", odmena);
				
			}
			
		}
		else if(c == 'p'){
			if(pole != NULL){
				char reverse[8];
				for(int i = 0; i < pocet; i++){
					int x = 0, palindrom = 0;
					for(int j = 6; j >= 0; j--){
						reverse[x] = pole[i].SPZ[j];
						x++;
					}
					palindrom = strcmp(reverse, pole[i].SPZ);

					if(palindrom == 0){
						printf("%s %s\n", pole[i].name_surname, pole[i].SPZ);
					}
				}
			}
		}
		else if(c == 'h'){
			int abeceda[26];
			for(int u = 0; u < 26; u++){
				abeceda[u] = 0;
			}
			for(int i = 0; i < pocet; i++){
				abeceda[((int)pole[i].SPZ[0])-65]++;
				abeceda[((int)pole[i].SPZ[1])-65]++;
			}
			for(int j = 0; j < 26; j++){
				if(abeceda[j] != 0){
					printf("%c: %d\n", j+65, abeceda[j]);
				}
			}
		}
		else if(c == 'c'){
			if(pole != NULL){
				int vyska_pokuty; 
				char hladana_SPZ[8];
				scanf("%d", &vyska_pokuty);
				scanf("%s", &hladana_SPZ);
				novy_pocet = pocet;
				
				for(int i = 0; i < pocet; i++){
					if(pole[i].pokuta < vyska_pokuty && pole[i].SPZ[0] == hladana_SPZ[0] && pole[i].SPZ[1] == hladana_SPZ[1]){
						pole[i].pohlavie = 'A';
						novy_pocet--;
					}
				}
				
				nove_pole = (struct novy_zaznam*)malloc((sizeof(struct novy_zaznam))*novy_pocet);
				int x = 0;
				for(int j = 0; j < pocet; j++){
					if(pole[j].pohlavie != 'A'){
						strcpy(nove_pole[x].name_surname,pole[j].name_surname);
						nove_pole[x].pohlavie = pole[j].pohlavie;
						nove_pole[x].rok_narodenia = pole[j].rok_narodenia;
						strcpy(nove_pole[x].SPZ, pole[j].SPZ);
						nove_pole[x].priestupok = pole[j].priestupok;
						nove_pole[x].pokuta = pole[j].pokuta;
						nove_pole[x].datum_priestupku = pole[j].datum_priestupku;
						x++;
 					}
				}
				for(int h = 0; h < novy_pocet; h++){
						printf("meno priezvisko: %s\n", nove_pole[h].name_surname);
						printf("pohlavie: %c\n", nove_pole[h].pohlavie);
						printf("rok narodenia: %d\n", nove_pole[h].rok_narodenia);
						printf("SPZ: %s\n", nove_pole[h].SPZ);
						printf("typ priestupku: %c\n", nove_pole[h].priestupok);
						printf("vyska pokuty: %d\n", nove_pole[h].pokuta);
						printf("datum priestupku: %d\n", nove_pole[h].datum_priestupku);
						printf("\n");
					}
			}
		}
		scanf("%c", &c);
		}		
	if(c == 'k'){
		ukonci(f);
		free(pole);
		exit(0);
	}	
	return 0;
}
