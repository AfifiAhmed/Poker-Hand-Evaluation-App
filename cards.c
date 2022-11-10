/*******************************************/
/*          Author: Ahmed Afifi            */        
/*          Date: 20-12-2021               */
/*          Version: 1.0                   */
/*          Module: Poker Evaulation Hand  */
/*******************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value>=2 && c.value <= VALUE_ACE && c.suit >= SPADES && c.suit <=CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  assert ( r == STRAIGHT_FLUSH||  FOUR_OF_A_KIND||FULL_HOUSE ||FLUSH||STRAIGHT|| THREE_OF_A_KIND||TWO_PAIR||PAIR|| NOTHING);
  switch(r){
  case STRAIGHT_FLUSH : return "STRAIGHT_FLUSH" ; break;
  case FOUR_OF_A_KIND : return "FOUR_OF_A_KIND" ; break;
  case FULL_HOUSE : return "FULL_HOUSE" ; break;
  case FLUSH : return "FLUSH" ; break;
  case STRAIGHT : return "STRAIGHT" ; break;
  case THREE_OF_A_KIND : return "THREE_OF_A_KIND" ; break;
  case TWO_PAIR : return "TWO_PAIR" ; break;
  case PAIR : return "PAIR" ; break;
  case NOTHING : return "NOTHING" ; break;
  default : break;
    }
  return "";
}

char value_letter(card_t c) {
  switch(c.value) {
  case 2 : return '2' ; break;
  case 3 : return '3' ; break;
  case 4 : return '4' ; break;
  case 5 : return '5' ; break;
  case 6 : return '6' ; break;
  case 7 : return '7' ; break;
  case 8 : return '8' ; break;
  case 9 : return '9' ; break;
  case 10 : return '0' ; break;
  case 11 : return 'J' ; break;
  case 12 : return 'Q' ; break;
  case 13 : return 'K' ; break;
  case 14 : return 'A' ; break;
  default : return ' ' ; break;
  }
  return 'x';
}


char suit_letter(card_t c) {
  if(c.suit == SPADES)
    return 's';
  if(c.suit == HEARTS)
    return 'h';
  if(c.suit == DIAMONDS)
    return 'd';
  if(c.suit == CLUBS)
    return 'c';

  return 'x';

}

void print_card(card_t c) {
  printf("%c%c ",value_letter(c),suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  assert( (value_let == '0' || 'K' || 'Q' || 'J'|| 'A') ||(value_let>='2' && value_let<='9'));
  assert((suit_let == 's'||'h'||'d'||'c'));
  switch (value_let){
  case '2' : temp.value =2  ; break;
  case '3' : temp.value =3 ; break;
  case '4' : temp.value =4 ; break;
  case '5' : temp.value = 5 ; break;
  case '6' : temp.value =  6; break;
  case '7' : temp.value = 7 ; break;
  case '8' : temp.value = 8 ; break;
  case '9' : temp.value = 9 ; break;
  case '0' : temp.value = 10 ; break;
  case 'J' : temp.value = 11 ; break;
  case 'Q' : temp.value = 12 ; break;
  case 'K' : temp.value = 13 ; break;
  case 'A' : temp.value = 14 ; break;

  default : break;
    }

  switch(suit_let){
  case 's' : temp.suit =SPADES ; break;
  case 'h' : temp.suit =HEARTS ; break;
  case 'd' : temp.suit =DIAMONDS ; break;
  case 'c' : temp.suit =CLUBS ; break;
  default :  break;

  }

  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;

  if(c<0 && c>=52)
    { printf("invalid input"); exit (EXIT_FAILURE);}
  else {
    temp.value = c%13;
    if ( temp.value== 0)
      temp.value = VALUE_KING;
    if(temp.value == 1)
      temp.value = VALUE_ACE;

  }

  if(c>=0  && c<=12  )
    temp.suit =SPADES  ;
  if(c>=13  && c<=25  )
    temp.suit =HEARTS  ;
  if(c>=26  && c<=38  )
    temp.suit =DIAMONDS  ;
  if(c>= 39 && c<=51  )
    temp.suit =CLUBS  ;

  return temp;
}
