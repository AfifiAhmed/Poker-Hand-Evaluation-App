/*******************************************/
/*          Author: Ahmed Afifi            */        
/*          Date: 20-12-2021               */
/*          Version: 1.0                   */
/*          Module: Poker Evaulation Hand  */
/*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
for (int i = 0; i<(*hand).n_cards ; i++)
{
    print_card(*hand->cards[i]);
}
}

int deck_contains(deck_t * d, card_t c) {
    for(int i =0 ; i<(*d).n_cards;i++)
    {
        if((*d->cards[i]).value == c.value && (*d->cards[i]).suit == c.suit);
            return EXIT_SUCCESS;

    }
  return 0;
}

void shuffle(deck_t * d){
    for(int i = 0; i<d->n_cards;i++)
    {
        d->cards[i] = &(*d->cards[i]);
    }

    size_t n = d->n_cards;
      for(int i = 0; i<d->n_cards;i++)
    {
        int temp = rand() %n + 0;
        card_t *swap = d->cards[i];
        d->cards[i] = d->cards[temp];
        d->cards[temp] = swap;
    }
}

void assert_full_deck(deck_t * d) {
    for(int i = 0; i<d->n_cards;i++)
    {
        assert_card_valid(*d->cards[i]);

    }

}

int main (void){
return 1;
}
