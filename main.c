#include<stdio.h>

// struct paciente
struct Patient{
	int status;
	int numberCard;
	float inputWeight;
	float outputWeight;
	char name[64];
	int amountOfDays;
	float days[30];
};

struct Patient createPatient(int numberCard){
	
	struct Patient patient;
	
	printf("\nCadastrando cliente, por favor digite as informacoes:\n\n");
	printf("********************* Ficha n");
	printf("%i **********************\n", numberCard);
	patient.numberCard = numberCard;
	printf("Nome: ");
	scanf("%s", &patient.name);
	printf("Peso atual (g): ");
	scanf("%f", &patient.inputWeight);
	printf("Quantidade de dias para o tratamento (max 30): ");
	scanf("%i", &patient.amountOfDays);
	printf("Quantidade de calorias por dia de tratamento: \n");
	int i;	
	for(i=0; i<patient.amountOfDays; i++){
		printf("Dia %i: ", (i+1));
		scanf("%f", &patient.days[i]);
	}
	printf("*****************************************************\n\n");
	printf("-----------------------------------------------------\n");
	return patient;
	
}

struct Patient discharge(struct Patient patient, float lost){
	patient.status = 1;
	patient.outputWeight = lost;
	return patient;
}

struct Patient initPatient(struct Patient patient){
	int i;
	
	patient.amountOfDays = 0;
	for(i=0; i<30; i++){
		patient.days[i] = 0;
	}	
	patient.inputWeight = 0;
	for(i=0; i<64; i++){
		patient.name[i] = 0;
	}	
	patient.numberCard = 0;
	patient.outputWeight = 0;
	patient.status = 0;
	return patient;
}

void showCard(struct Patient patient){
	printf("********************* Ficha n");
	printf("%i **********************\n", patient.numberCard);
	printf("Status: ");
	if(patient.status == 0){
		printf("HOSPEDADO\n");
	}else{
		printf("ALTA\n");
	}
	printf("Peso ao entrar (g): %.2f\n", patient.inputWeight);
	if(patient.status == 1){
		printf("Peso ao sair   (g): %.2f\n", patient.outputWeight);
	}
	printf("Nome: %s\n", patient.name);
	printf("Dias de tratamento: %i\n", patient.amountOfDays);
	printf("Quantidade de calorias por dia de tratamento: \n");
	int i;
	for(i=0; i<patient.amountOfDays; i++){
		printf("Dia %i: %.0f\n", (i+1), patient.days[i]);
	}
	printf("*****************************************************\n\n");
	printf("-----------------------------------------------------\n");	
}


main(){
	
	struct Patient patients[20];
	int numberCard = 1;
	int i;
	
	for(i=0; i<20; i++){
		patients[i] = initPatient(patients[i]);
	}
	
	int choice;
	
	do{
		printf("Escolha uma acao:\n 0. Encerrar Programa\n 1. Cadastrar paciente\n 2. Dar alta\n 3. Visualizar fichas\ncommand: ");
		scanf("%i", &choice);
		printf("-----------------------------------------------------\n");
		
		if(choice == 1){
			if(numberCard<=20){
				patients[(numberCard-1)] = createPatient(numberCard);
				numberCard++;
			}else{
				printf("Nao eh possivel cadastrar mais pacientes!!");	
			}			
		}else if(choice == 2){
			
			int status = 0;
			for(i=0; i<20; i++){
				if(patients[i].numberCard > 0 && patients[i].status == 0){
					status = 1;
					break;
				}
			}
			
			if(status == 1){
				int number;
				printf("Deseja dar alta a qual paciente?\n");
				for(i=0; i<20; i++){
					if(patients[i].numberCard > 0){
						printf(" %i. %s\n", patients[i].numberCard, patients[i].name);
					}
				}	
				printf("command: ");
				scanf("%i", &number);
				printf("\n");
				float lost;
				printf("Digite o peso do paciente ao final do tratamento: ");
				scanf("%f", &lost);
				patients[(number-1)] = discharge(patients[(number-1)], lost);
				printf("O paciente %s recebeu alta!\n", patients[(number-1)].name);
				printf("-----------------------------------------------------\n");
			}else{
				printf("Nao existem pacientes para dar alta\n");
				printf("-----------------------------------------------------\n");
			}						
		}else if(choice == 3){
			int hasCard = 0;
			
			for(i=0; i<20; i++){
				if(patients[i].numberCard > 0){
					hasCard = 1;
					break;
				}
			}
			
			if(hasCard == 1){
				int number;
				printf("Deseja visualizar qual ficha?\n");
				for(i=0; i<20; i++){
					if(patients[i].numberCard > 0){
						printf(" %i. %s\n", patients[i].numberCard, patients[i].name);
					}
				}
				printf("command: ");
				scanf("%i", &number);
				printf("\n");
				showCard(patients[(number-1)]);
			}else{
				printf("Nao existem fichas para visualizar\n");
				printf("-----------------------------------------------------\n");
			}
		}
			
	}while (choice != 0);
	
}
