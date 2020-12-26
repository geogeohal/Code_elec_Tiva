#include "whiteScreen.h"
#include "test_2.h"
#include "IsepScreen.h"
#include "iseplogo128.h"
#include "capteur_temp_image.h"


void setup() {

Serial.begin(9600); //fréquence d'envoie des datas aux pc qui est relié au microcontrôleur, pour affichage dans des tableaux par la suite

InitI2C(); // initialisation de l'écran
InitScreen();
Display(whiteScreen); // effaçage de l'écran


Display(logo_groupe); // affichage du logo du groupe
delay(1000);  // temps d'attente (en ms)
Display(IsepScreen); // affichage de "- app - ISEP"
delay(1500); // temps d'attente (en ms)
Display(logo_groupe); // affichage du logo du groupe
delay(1500); // temps d'attente (en ms)
Display(motif); // affichage du logo de l'ISEP
delay(1500); // temps d'attente (en ms)
Display(logo_capteur_temperature); // affichage du logo de l'ISEP
delay(1500);
Display(whiteScreen); // effaçage de l'écran.


}

void loop() {


  float somme_temp = 0.0; // initialisation de la somme des températures

  int nb_iteration = 100; //nombre d'itérations de le prises de tempérture instantanée donnée par le capteur durant la durée "temps_rafraîchissement_image"
  int temps_rafraichissement_image = 1000; //durée en millisecondes entre deux rafraîchissements de l'écran (en ms)
  int delais = temps_rafraichissement_image / nb_iteration; //calcul du délai entre chaque mesure de température instantanée (en ms)



  for(int i=0; i < nb_iteration; i++){   //boucle de prises de températures instantanées
   int valeur_brute = analogRead(PD_3); // prise de la valeur analogue donnée à la pin PD3
   float temperature_celcius = valeur_brute * 3.3 / 4095 * 100; //calcul de la température en degrés celcius
   // 3.3 = tension de la carte (en V)
   // 4095 = nombre de valeurs que peut prendre analogRead pour décrire la tension à la pin PD3 (0 = 0V et 4095 = 3.3 V)
   // 100 = température maximale que peut mesurer le capteur de température
   somme_temp = somme_temp + temperature_celcius; // ajout de la valeur instantanée pour calculer la moyenne après

   delay(delais);
  }
  
  float moy_temp = somme_temp / nb_iteration ; // calcul de la température moyenne sur l'interval de temp "temps rafraîchissement image"


  Serial.println(moy_temp); //affichage dans energia de la valeur de la température moyenne

  char moy_temp_char[16]; // initialisation de moy_temp_char
  itoa(moy_temp, moy_temp_char, 10); // transformation de l'integer moy_temp en moy_temp_char
  DisplayString(0,5,"          "); // blanc permettant l'effaçage de la valeur précédente
  DisplayString(0,5,moy_temp_char); // affichage de la valeur moyenne de la température
  DisplayString(15,5,"°C"); // affichage de "°C" à la suite de la valeur


}
