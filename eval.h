/*******************************************/
/*          Author: Ahmed Afifi            */        
/*          Date: 02-01-2022               */
/*          Version: 1.0                   */
/*          Module: Poker Evaulation Hand  */
/*******************************************/
#ifndef EVAL_H
#define EVAL_H
#include "deck.h"
struct hand_eval_tag {
  hand_ranking_t ranking;
  card_t *cards[5];
};
typedef struct hand_eval_tag hand_eval_t;


int largest_value(deck_t *hand, size_t size);
//int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) ;
//int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs);
hand_eval_t evaluate_hand(deck_t * hand) ;
int compare_hands(deck_t * hand1, deck_t * hand2) ;

#endif
