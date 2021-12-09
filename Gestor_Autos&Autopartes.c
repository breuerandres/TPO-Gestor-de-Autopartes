#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50
#define ARCH_PARTES "catalogo_autopartes.bin"
#define ARCH_AUTOS "catalogo_automoviles.bin"

// Estructuras

typedef struct strAutoParte{
	int codigoProd;
	char descripcion[10*MAX];
	int stockProd;
	char modelo[MAX];
	int costo;
	char planta[MAX];	
}tAutoParte;

typedef struct strNodoAutoParte {
	tAutoParte pieza;
	struct strNodoAutoParte *sig;
}tNodoAutoParte;

//typedef tNodoAutoParte * tPtrAutoParte;

typedef struct strAutomovil{
	char modelo[MAX];
	int puertas;
	char motor[MAX];
	char planta[MAX];
	int anio;
	
}tAutomovil;

// Funciones de menu

void menuPrincipal();
void menuAutoPartes();
void menuAutoMoviles();

// Funciones de Autopartes

void altaAutoPartes();
void bajaAutoPartes();
void modifAutoPartes();
void mostrarAutoPartes();

// Funciones de Automoviles

void altaAutoMovil();
void bajaAutoMovil();
void modifAutoMovil();
void mostrarAutoMovil();

// Otras funciones

void verifArch(char nom[]);
int yaExisteParte(int codigo);
int yaExisteAuto(tAutomovil item);
void filtroStock();

int main(){
	
	menuPrincipal();
	
	return 0;
}


void menuPrincipal(){
	int repite = 1;
	int opcion;
	do{
		system("cls");
	
		printf("\n\t\t\t--MENU PRINCIPAL--\n\n");
    	printf("\t1 - Menu de Autopartes\n");
   		printf("\t2 - Menu de Automoviles\n");	
    	printf("\t3 - Salir\n\n");
    	printf("\tIngrese su opcion: ");
    	scanf("%d",&opcion);
    	
    	switch (opcion) {
    		
    		case 1:
    			menuAutoPartes();
    			break;
    		
    		case 2:
    			menuAutoMoviles();
    			break;
    			
    		case 3:
    			repite = 0;
    			break;
		} 
	}while (repite);
	
}

void menuAutoPartes(){
	int repite = 1;
	int opcion;
	do{
		system("cls");
	
		printf("\n\t\t\t-MENU AUTOPARTES-\n\n");
    	printf("\t1 - Alta\n");
   		printf("\t2 - Baja\n");
		printf("\t3 - Modificacion\n");
		printf("\t4 - Mostrar catalogo\n");
		printf("\t5 - Filtrar por Stock\n");	
    	printf("\t6 - Volver al MENU PRINCIPAL\n\n");
    	printf("\tIngrese su opcion: ");
    	scanf("%d",&opcion);
    	
    	switch (opcion) {
    		
    		case 1:
    			altaAutoPartes();
    			break;
    		
    		case 2:
    			bajaAutoPartes();
    			break;
    			
    		case 3:
    			modifAutoPartes();
    			break;
    			
    		case 4:
    			mostrarAutoPartes();
    			break;
    			
    		case 5:
    			filtroStock();
    			break;
    			
    		case 6:
    			repite = 0;
    			break;
		} 
	}while (repite);
	
}

void menuAutoMoviles(){
	int repite = 1;
	int opcion;
	do{
		system("cls");
	
		printf("\n\t\t\t-MENU AUTOMOVILES-\n\n");
    	printf("\t1 - Alta\n");
   		printf("\t2 - Baja\n");
		printf("\t3 - Modificacion\n");
		printf("\t4 - Mostrar catalogo\n");	
    	printf("\t5 - Volver al MENU PRINCIPAL\n\n");
    	printf("\tIngrese su opcion: ");
    	scanf("%d",&opcion);
    	
    	switch (opcion) {
    		
    		case 1:
    			altaAutoMovil();
    			break;
    		
    		case 2:
    			bajaAutoMovil();
    			break;
    			
    		case 3:
    			modifAutoMovil();
    			break;
    			
    		case 4:
    			mostrarAutoMovil();
    			break;
    			
    		case 5:
    			repite = 0;
    			break;
		} 
	}while (repite);
	
	
}

void altaAutoPartes(){
	
	verifArch(ARCH_PARTES);
	FILE *f;
	
	tAutoParte parte;	
	system ("cls");
	
	printf("\n\t\t\t-INGRESE LOS DATOS DE LA PIEZA-\n\n\n");
	printf("\tCodigo (Ingrese 0 para dejar de ingresar): ");
	scanf("%d",&parte.codigoProd);
	
	// Verificamos la existencia del producto
	while (yaExisteParte(parte.codigoProd)){ 
		printf("\n\tLa pieza con ese codigo ya existe.\n");
		printf("\tCodigo (Ingrese 0 para dejar de ingresar): ");
		scanf("%d",&parte.codigoProd);
	}
						
	while (parte.codigoProd != 0){
		printf("\n\tDescripcion: ");
		fflush(stdin);
		gets(parte.descripcion);
		printf("\n\tCantidad en Stock: ");
		scanf("%d",&parte.stockProd);
		printf("\n\tPara auto modelo: ");
		fflush(stdin);
		gets(parte.modelo);
		printf("\n\tCosto: ");
		scanf("%d",&parte.costo);
		printf("\n\tPlanta de destino: ");
		fflush(stdin);
		gets(parte.planta);
		
		
		f = fopen(ARCH_PARTES,"ab"); // Abro el archivo
		if (f==NULL){
			printf("ERROR - No se pudo abrir el archivo.");
			exit(1);
		}
		fwrite(&parte,sizeof(tAutoParte),1,f); // Escribo el registro
		if (fclose(f)!=0){ // Cierro el archivo
			printf("No se pudo cerrar el archivo");
		}
		
		printf("\n\n\tIngreso Exitoso! Presione ENTER para continuar.\n\n");
		getchar();
		system ("cls");
		printf("\n\t\t\tINGRESE LOS DATOS DE LA PIEZA\n\n");
		printf("\tCodigo (Ingrese 0 para dejar de ingresar): ");
		scanf("%d",&parte.codigoProd);
		
		// Verificamos la existencia del producto
		while (yaExisteParte(parte.codigoProd)){ 
			printf("\n\tLa pieza con ese codigo ya existe.\n");
			printf("\tCodigo (Ingrese 0 para dejar de ingresar): ");
			scanf("%d",&parte.codigoProd);
		}
		
	}
	
}

void bajaAutoPartes(){
	
	char confirma = 's';
	int existe = 0;
	int baja;
	tAutoParte pieza;
	FILE *f;
	system("cls");
	
	printf("\n\t\t\t-BAJA DE AUTO PARTES-\n\n\n");
	
	f = fopen(ARCH_PARTES,"rb+"); // Abro el archivo
		if (f==NULL){
			printf("\tERROR - No se pudo abrir el archivo.\n");
			exit(1);
		}
		
	printf("\tIngrese el codigo de producto que desea eliminar (0 para cancelar): ");
	scanf("%d",&baja);
	
	if(baja != 0){
		fread(&pieza,sizeof(tAutoParte),1,f);
		
		while(!feof(f) && existe==0){
			if(pieza.codigoProd==baja){
				
				printf("\n\tDesea eliminar el siguiente producto?\n\n");
				printf("\t|%d|%s|%s|\n\n",pieza.codigoProd,pieza.descripcion,pieza.modelo);
				printf("\tPresione 's' para confirmar: ");
				fflush(stdin);
				confirma = tolower(getchar());
				
				if(confirma=='s'){
					fseek(f,ftell(f) - sizeof(tAutoParte),SEEK_SET);
					pieza.codigoProd = -1;
					fwrite(&pieza,sizeof(tAutoParte),1,f);
					existe = 1;
				}
					
			}
			fseek(f,0,SEEK_CUR);
			fread(&pieza,sizeof(tAutoParte),1,f);
									
		}	
		if (existe==0){
			printf("\tNo se encontro el producto buscado");
		}
	}
	if (fclose(f)!=0){
		printf("No se pudo cerrar el archivo");
	}	
}

void modifAutoPartes(){
	
	char confirma = 's';
	int existe = 0;
	int modif;
	tAutoParte pieza;
	FILE *f;
	system("cls");
	
	printf("\n\t\t\t-MODIFICAR AUTO PARTES-\n\n\n");
		
	printf("\tIngrese el codigo de producto que desea modificar (0 para cancelar): ");
	scanf("%d",&modif);
	
	if(modif != 0){
		
		f = fopen(ARCH_PARTES,"rb+"); // Abro el archivo
		if (f==NULL){
			printf("\tERROR - No se pudo abrir el archivo.\n");
			exit(1);
		}
		
		fread(&pieza,sizeof(tAutoParte),1,f);
		
		while(!feof(f) && existe==0){
			if(pieza.codigoProd==modif){
				
				printf("\n\tDesea modificar el siguiente producto?\n\n");
				printf("\t | %d | %s | %s |\n\n",pieza.codigoProd,pieza.descripcion,pieza.modelo);
				printf("\tPresione 's' para confirmar: ");
				fflush(stdin);
				confirma = tolower(getchar());
				printf("\n");
				
				if(confirma=='s'){
					
					fseek(f,ftell(f) - sizeof(tAutoParte),SEEK_SET);
					
					printf("\tCodigo: ");
					scanf("%d",&pieza.codigoProd);
					printf("\n\tDescripcion: ");
					fflush(stdin);
					gets(pieza.descripcion);
					printf("\n\tCantidad en Stock: ");
					scanf("%d",&pieza.stockProd);
					printf("\n\tPara auto modelo: ");
					fflush(stdin);
					gets(pieza.modelo);
					printf("\n\tCosto: ");
					scanf("%d",&pieza.costo);
					printf("\n\tPlanta de destino: ");
					fflush(stdin);
					gets(pieza.planta);
					
					fwrite(&pieza,sizeof(tAutoParte),1,f);
					existe = 1;
				}
					
			}
			fseek(f,0,SEEK_CUR);
			fread(&pieza,sizeof(tAutoParte),1,f);
									
		}
		if (fclose(f)!=0){
			printf("No se pudo cerrar el archivo");
		}
		
		if (existe==0){
			printf("\n\tNo se encontro el producto buscado");
		}	
		
	
	}
	
}

void filtroStock(){
	
	char confirm;
	int cant,cont;
	int primero = 0;
	tAutoParte parte;
	tNodoAutoParte *cabeza = NULL;
	tNodoAutoParte *nuevo;
	tNodoAutoParte *actual;		
	FILE *f;
		
	system("cls");
	
	printf("\n\t\t\t-FILTRAR POR STOCK-\n\n\n");
	printf("\tMostrar stock menor a (-1 para volver): ");
	scanf("%d",&cant);
	
	// Leemos los registros y armamos la lista dinamica
	if (cant>=0){
		f = fopen(ARCH_PARTES,"rb");
		if (f==NULL){
			printf("\tERROR - No se pudo abrir el archivo.\n");
			exit(1);
		}
		
		// Creo el primer nodo y lo defino como cabeza.
		
		fread(&parte,sizeof(tAutoParte),1,f);
		while (!feof(f) && primero==0){			
			if (parte.stockProd<cant && parte.codigoProd != -1){
				nuevo = malloc(sizeof(tNodoAutoParte));
				nuevo->pieza = parte;
				nuevo->sig = NULL;
				cabeza = nuevo;
				actual = nuevo;
				primero = 1;
			}
			fread(&parte,sizeof(tAutoParte),1,f);	
		}
		// Inserto el resto
		while (!feof(f) && primero == 1){
			if (parte.stockProd<cant && parte.codigoProd != -1){
				nuevo = malloc(sizeof(tNodoAutoParte));
				nuevo->pieza = parte;
				nuevo->sig = NULL;
				actual->sig = nuevo;
				actual = nuevo;				
			}
			fread(&parte,sizeof(tAutoParte),1,f);
		}
		
		if (fclose(f)!=0){ // Cierro el archivo
				printf("No se pudo cerrar el archivo");
			}
		
		if (primero == 0){
			printf("\n\tTodos los productos tienen mas de %d items en stock.",cant);
		}
		else {
			// Imprimir valores en pantalla
			
			printf("--------------------------------------------------------------------------------\n");
			printf("| %s |        %s        | %s |   %s   | %s |   %s   |\n","Codigo","Descripcion","Stock","Modelo","Costo","Planta");
			printf("--------------------------------------------------------------------------------\n");
			
			actual = cabeza;
			while (actual!=NULL){
				printf("|%8d|%27s|%7d|%12s|%7d|%12s|\n",actual->pieza.codigoProd,actual->pieza.descripcion,actual->pieza.stockProd,actual->pieza.modelo,actual->pieza.costo,actual->pieza.planta);
				actual = actual->sig;
			}
			printf("--------------------------------------------------------------------------------\n");
			
			// Preguntar si desea exportar a csv
			
			printf("\nDesea exportar el listado a un archivo csv? [s]i - [n]o : ");
			fflush(stdin);
			confirm = getchar();
			
			// Exportar csv
			
			if (confirm == 's'){
				
				FILE *csv = fopen("catalogo_stock.csv","w");
				if (csv==NULL){
					printf("\tNo se pudo crear el archivo");
					exit(1);
				}
				
				fprintf(csv,"Codigo,Descripcion,Stock,Modelo,Costo,Planta\n");
				
								
				actual = cabeza;
				cont = 1;
				while (actual != NULL){					
					fprintf(csv,"%d,%s,%d,%s,%d,%s\n",actual->pieza.codigoProd,actual->pieza.descripcion,actual->pieza.stockProd,actual->pieza.modelo,actual->pieza.costo,actual->pieza.planta);					
					actual = actual->sig;	
					cont++;		
				}
				
				fprintf(csv,"\n");
				fprintf(csv," ,Suma,=sum(C2:C%d),",cont);
				if (fclose(csv)!=0){ // Cierro el archivo
				printf("No se pudo cerrar el archivo");
				}
			}
			
			// Liberar memoria
			
			actual = cabeza;
			while (actual!=NULL){
				actual = cabeza->sig;
				free(cabeza);
				cabeza = actual;
			}
		}
	}	
	printf("\n\n\tPresione ENTER para volver atras");
	fflush(stdin);
	getchar();
}

void mostrarAutoPartes(){
	
	tAutoParte pieza;
	FILE *f;
	system("cls");
	
	printf("\n\t\t\t-CATALOGO AUTO PARTES-\n\n");
	
	f = fopen(ARCH_PARTES,"rb+"); // Abro el archivo
		if (f==NULL){
			printf("\tERROR - No se pudo abrir el archivo.\n");
			exit(1);
		}
		
	printf("--------------------------------------------------------------------------------\n");
	printf("| %s |        %s        | %s |   %s   | %s |   %s   |\n","Codigo","Descripcion","Stock","Modelo","Costo","Planta");
	printf("--------------------------------------------------------------------------------\n");	
	
	fread(&pieza,sizeof(tAutoParte),1,f);
	
	while(!feof(f)){
		if (pieza.codigoProd != -1){
			printf("|%8d|%27s|%7d|%12s|%7d|%12s|\n",pieza.codigoProd,pieza.descripcion,pieza.stockProd,pieza.modelo,pieza.costo,pieza.planta);			
		}
		fread(&pieza,sizeof(tAutoParte),1,f);		
	}
	
	if (fclose(f)!=0){ // Cierro el archivo
				printf("No se pudo cerrar el archivo");
			}
			
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n\tPresione ENTER para volver atras");
	fflush(stdin);
	getchar();
}

void altaAutoMovil(){
	int cant;
	verifArch(ARCH_AUTOS);
	FILE *f;
	f = fopen(ARCH_AUTOS,"rb+");
	
	tAutomovil autos;	
	system ("cls");
	
	printf("\n\t\t\t-INGRESE LOS DATOS DEL AUTOMOVIL-\n\n\n");
	printf("\tANIO (Ingrese 0 para dejar de ingresar): ");
	scanf("%d",&autos.anio);
	
	while (autos.anio != 0){
		printf("\n\tModelo: ");
		fflush(stdin);
		gets(autos.modelo);
		
		printf("\n\tCantidad de puertas: ");
		scanf("%d",&autos.puertas);
		
		printf("\n\tMotor: ");
		fflush(stdin);
		gets(autos.motor);
		
		printf("\n\tPlanta de destino: ");
		fflush(stdin);
		gets(autos.planta);
		
		if(yaExisteAuto(autos)){ 
			printf("\n\tEse automovil ya fue ingresado.\n\n");
		}else{
			f = fopen(ARCH_AUTOS,"ab"); // Abro el archivo
			if (f==NULL){
				printf("ERROR - No se pudo abrir el archivo.");
				exit(1);
			}
			fwrite(&autos,sizeof(autos),1,f); // Escribo el registro
			if (fclose(f)!=0){ // Cierro el archivo
				printf("No se pudo cerrar el archivo");
			}
		
			printf("\n\n\tIngreso Exitoso! Presione ENTER para continuar.");
			fflush(stdin);
			getchar();
			system ("cls");
			printf("\n\t\t\t-INGRESE LOS DATOS DEL AUTOMOVIL-\n\n\n");
			}
		printf("\tANIO (Ingrese 0 para dejar de ingresar): ");
		scanf("%d",&autos.anio);
	}
}

void bajaAutoMovil(){
	
	char confirma = 's';
	int existe = 0;
	int anio = 0;
	int puertas = 0;
	char modelo[MAX];
	char motor[MAX];
	char planta[MAX];
	
	tAutomovil autos;
	FILE *f;
	system("cls");
	
	printf("\n\t\t\t-BAJA DE AUTOMOVILES-\n\n\n");
	
	f = fopen(ARCH_AUTOS,"rb+"); // Abro el archivo
		if (f==NULL){
			printf("\tERROR - No se pudo abrir el archivo.\n");
			exit(1);
		}
		
	printf("\tIngrese el anio del vehiculo que desea eliminar (0 para cancelar): ");
	scanf("%d",&anio);	
	
	if(anio != 0){
		printf("\n\tModelo: ");
		fflush(stdin);
		gets(modelo);	
		printf("\n\tCantidad de puertas: ");
		scanf("%d", &puertas);
		printf("\n\tMotor: ");
		fflush(stdin);
		gets(motor);	
		printf("\n\tPlanta: ");
		fflush(stdin);
		gets(planta);
		
		fread(&autos,sizeof(autos),1,f);
		
		while(!feof(f) && existe==0){
			if((autos.anio==anio)&&(!strcmp(autos.modelo, modelo))&&(!strcmp(autos.motor, motor))
									&& (!strcmp(autos.planta, planta))&&(autos.puertas==puertas)){
				
				printf("\n\tDesea eliminar el siguiente producto?\n\n");
				printf("\t|%d|%s|%d|%s|%s|\n\n",autos.anio,autos.modelo,autos.puertas,autos.motor,autos.planta);
				printf("\tPresione 's' para confirmar: ");
				fflush(stdin);
				confirma = tolower(getchar());
				
				if(confirma=='s'){
					fseek(f,ftell(f) - sizeof(autos),SEEK_SET);
					autos.anio = -1;
					fwrite(&autos,sizeof(autos),1,f);
					existe = 1;
				}
					
			}
			fseek(f,0,SEEK_CUR);
			fread(&autos,sizeof(autos),1,f);
									
		}	
		if(existe==0){
			printf("\tNo se encontro el automovil buscado");
			printf("\n\n\tPresione ENTER para volver al menu.\n\n");
			fflush(stdin);
			getchar();
		}
	}
	if (fclose(f)!=0){
		printf("No se pudo cerrar el archivo");
	}	
}

void modifAutoMovil(){
	
	char confirma = 's';
	int existe = 0;
	int anio = 0;
	char modelo[MAX];
	char motor[MAX];
	char planta[MAX] ;
	int puertas = 0;
	
	tAutomovil autos;
	FILE *f;
	system("cls");
	
	printf("\n\t\t\t-MODIFICAR AUTOMOVILES-\n\n\n");
		
	printf("\tIngrese el anio del producto que desea modificar (0 para cancelar): ");
	scanf("%d",&anio);
	
	if(anio != 0){
		printf("\n\tModelo: ");
		fflush(stdin);
		gets(modelo);
		
		printf("\n\tCantidad de puertas: ");
		scanf("%d", &puertas);
		
		printf("\n\tMotor: ");
		fflush(stdin);
		gets(motor);
		
		printf("\n\tPlanta: ");
		fflush(stdin);
		gets(planta);
				
		f = fopen(ARCH_AUTOS,"rb+"); // Abro el archivo
		if (f==NULL){
			printf("\tERROR - No se pudo abrir el archivo.\n");
			exit(1);
		}
		
		fread(&autos,sizeof(autos),1,f);
		
		while(!feof(f) && existe==0){
			if((autos.anio==anio)&&(!strcmp(autos.modelo, modelo))&&(!strcmp(autos.motor, motor))
								&& (!strcmp(autos.planta, planta))&&(autos.puertas==puertas)){
				
				printf("\n\tDesea modificar el siguiente producto?\n\n");
				printf("\t|%d|%s|%d|%s|%s|\n\n",autos.anio,autos.modelo,autos.puertas,autos.motor,autos.planta);
				printf("\tPresione 's' para confirmar: ");
				fflush(stdin);
				confirma = tolower(getchar());
				printf("\n");
				
				if(confirma=='s'){
					
					fseek(f,ftell(f) - sizeof(autos),SEEK_SET);
					
					printf("\tAnio: ");
					scanf("%d",&autos.anio);
					
					printf("\n\tModelo: ");
					fflush(stdin);
					gets(autos.modelo);
					
					printf("\n\tCantidad de puertas: ");
					scanf("%d",&autos.puertas);
					
					printf("\n\tMotor: ");
					fflush(stdin);
					gets(autos.motor);
					
					printf("\n\tPlanta: ");
					fflush(stdin);
					gets(autos.planta);
					
					fwrite(&autos,sizeof(autos),1,f);
					existe = 1;
				}
					
			}
			fseek(f,0,SEEK_CUR);
			fread(&autos,sizeof(autos),1,f);
									
		}
		if (fclose(f)!=0){
			printf("No se pudo cerrar el archivo");
		}
		
		if (existe==0){
			printf("\n\tNo se encontro el producto buscado");
		}	
		
	
	}
	
}

void mostrarAutoMovil(){
	
	tAutomovil autos;
	FILE *f;
	system("cls");
	
	printf("\n\t\t\t-CATALOGO DE AUTOMOVILES-\n\n");
	
	f = fopen(ARCH_AUTOS,"rb+"); // Abro el archivo
		if (f==NULL){
			printf("\tERROR - No se pudo abrir el archivo.\n");
			exit(1);
		}
		
	printf("----------------------------------------------------------\n");
	printf("| %s |    %s    | %s |   %s   |   %s   |\n","Anio","Modelo","Puertas","Motor","Planta");
	printf("----------------------------------------------------------\n");	
	
	fread(&autos,sizeof(autos),1,f);
	
	while(!feof(f)){
		if (autos.anio != -1){
			printf("|%6d|%14s|%9d|%11s|%12s|\n",autos.anio,autos.modelo,autos.puertas,autos.motor,autos.planta);			
		}
		fread(&autos,sizeof(autos),1,f);		
	}
	printf("----------------------------------------------------------\n");
	
	if (fclose(f)!=0){ // Cierro el archivo
				printf("No se pudo cerrar el archivo");
			}
	
	printf("\n\n\tPresione ENTER para volver atras");
	fflush(stdin);
	getchar();
}

void verifArch(char nom[]){ //Verificamos la existencia del archivo
	char confirm;
	FILE *f;
	f = fopen(nom,"rb+");
	
	printf("\n");
	if (f==NULL){ // Si no lo puede abrir en "rb+", es que no debe exixtir
		printf("\tERROR - El archivo no se pude abrir.\n");
		printf("\tProbablemente el archivo no exista. Desea crearlo?\n");
		printf("\t[s]i - [n]o: ");
		fflush(stdin);
		confirm = tolower(getchar());
		
		if (confirm=='s'){
			f = fopen(nom,"wb"); // Lo creamos, pero igual se verifica que se pueda abrir
			if (f==NULL){
				printf("ERROR - No se pudo crear el archivo.");
				exit(1);
			}
		}
		else{
			printf("ERROR - No se pudo crear el archivo.");
			exit(1);
		}
		
	}
	if(fclose(f)!=0){ 
		printf("El archivo no se pudo cerrar.\n"); // Se verifica que cierre sin problemas.
	}
}

int yaExisteParte(int codigo){	
	int existe = 0;	
	tAutoParte pieza;
	FILE * f = fopen(ARCH_PARTES,"rb");
	if (f==NULL){
		printf("ERROR - No se pudo crear el archivo.");
		exit(1);
	}
	fread(&pieza,sizeof(tAutoParte),1,f);
	while(!feof(f) && existe==0){
		if(pieza.codigoProd==codigo){
			existe = 1;		
		}
		fread(&pieza,sizeof(tAutoParte),1,f);
	}
	if (fclose(f)!=0){
		printf("No se pudo cerrar el archivo");
	}
	return existe;
}

int yaExisteAuto(tAutomovil item){
	int existe = 0;	
	tAutomovil autos;
	FILE * f = fopen(ARCH_AUTOS,"rb");
	if (f==NULL){
		printf("ERROR - No se pudo crear el archivo.");
		exit(1);
	}
	fread(&autos,sizeof(autos),1,f);
	while(!feof(f) && existe==0){
		if ((!strcmp(autos.modelo, item.modelo))&& 
			(autos.anio==item.anio)&&
			(!strcmp(autos.motor, item.motor))&&
			(autos.puertas==item.puertas)&&
			(!strcmp(autos.planta, item.planta))){
			
			existe = 1;		
		}
		fread(&autos,sizeof(autos),1,f);
	}
	if (fclose(f)!=0){
		printf("No se pudo cerrar el archivo");
	}
	return existe;	
}




