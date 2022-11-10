/*******************************************/
/*          Author: Ahmed Afifi            */        
/*          Date: 02-01-2022               */
/*          Version: 1.0                   */
/*          Module: Poker Evaulation Hand  */
/*******************************************/

#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
   const card_t * const *cp1 = vp1;
  const card_t * const *cp2 = vp2;
  if((*cp1)->value > (*cp2)->value)
    return -1;
  if((*cp1)->value < (*cp2)->value)
    return 1;
  if((*cp1)->value == (*cp2)->value)
    {
      if((*cp1)->suit < (*cp2)->suit)
      return 1;
      if((*cp1)->suit > (*cp2)->suit)
      return -1;
    }
  return 0;
}

suit_t flush_suit(deck_t * hand) {
  suit_t max_suit;
  for(int i = 0;i < hand->n_cards;i++)
    {
      int count = 0;
      for(int j = 1 ;j < hand->n_cards;j++)
	{
	  if(hand->cards[i]->suit == hand->cards[j]->suit)
	    count++;
	}
      if(count >= 5)
	  {
	  max_suit = hand->cards[i]->suit;
	  return max_suit;
	  }
    }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max = arr[0];
  for(int i = 1; i < n; i++)
    {
      if(max < arr[i])
	max = arr[i];
    }
  return max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for(int i = 0; i < n; i++)
    {
      if(match_counts[i] == n_of_akind)
	return i;
    }
  return 0;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  for(int i = 0; i < hand->n_cards; i++)
    {
      if(match_counts[i] >1 && hand->cards[i]->value != hand->cards[match_idx]->value)
	return i;
    }
  return -1;
}




int is_straight_at(deck_t * hand, size_t index, suit_t fs) {


  return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  ans.ranking = what;
  for (int i = 0; i < n; i++)
    {
      ans.cards[i] = hand->cards[idx];
      idx++;
    }
  idx = idx - n;

  if(what == NOTHING)
    {
      for(int i = 0; i < 5; i++)
	ans.cards[i] = hand->cards[i];
    }
  if(what == FOUR_OF_A_KIND)
    {
      if(idx == 0)
	ans.cards[4] = hand->cards[4];
      if(idx >= 1)
	ans.cards[4] = hand->cards[0];
    }
  if(what == THREE_OF_A_KIND)
    {
      if(idx == 0)
	{
	  ans.cards[3] = hand->cards[3];
	  ans.cards[4] = hand->cards[4];
	}
      if(idx == 1)
	ans.cards[3] = hand->cards[0];
      if(idx >=2 )
	{
	  ans.cards[3] = hand->cards[0];
	  ans.cards[4] = hand->cards[1];
	}

    }
  if(what == PAIR)
    {
       if(idx == 0)
	{
	  for(int i = 2;i < 5; i++)
	    ans.cards[i] = hand->cards[i];
	}
      if(idx == 1)
	ans.cards[2] = hand->cards[0];
      if(idx ==2 )
	{
	  ans.cards[2] = hand->cards[0];
	  ans.cards[3] = hand->cards[1];
	}
      if(idx >= 3)
	{
	  for(int i = 0;i < 3; i++)
	    ans.cards[i+2] = hand->cards[i];
	}

    }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  hand_eval_t h1,h2;
  h1 = evaluate_hand(hand1);
  h2 = evaluate_hand(hand2);
  if(h1.ranking == h2.ranking)
    {
      for(int i = 0;i < 5 ; i++)
	{
	  if(h1.cards[i]->value > h2.cards[i]->value)
	    return 1;
	 else if(h1.cards[i]->value < h2.cards[i]->value)
	    return -1;
	 else
	    continue;
	}
      return 0;
    }
  if(h1.ranking > h2.ranking)
    return -1;
  if(h1.ranking < h2.ranking)
    return 1;

  return 0;
}




unsigned * get_match_counts(deck_t * hand) ;



//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}



int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {   //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
