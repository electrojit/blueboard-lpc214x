/*
TNKernel real-time kernel

Copyright � 2004,2005 Yuri Tiomkin
All rights reserved.

Permission to use, copy, modify, and distribute this software in source
and binary forms and its documentation for any purpose and without fee
is hereby granted, provided that the above copyright notice appear
in all copies and that both that copyright notice and this permission
notice appear in supporting documentation.

THIS SOFTWARE IS PROVIDED BY THE YURI TIOMKIN AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL YURI TIOMKIN OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
*/

/* ver 2.0  */

#include "tn.h"

//----------------------------------------------------------------------------
//-- Circular double-linked list queue
//----------------------------------------------------------------------------

//-- queue reset(init)
void queue_reset(CDLL_QUEUE *que)
{
   que->prev = que->next = que;
}

//-- queue_empty
int is_queue_empty(CDLL_QUEUE *que)
{
   if(que->next == que && que->prev == que)
      return TRUE;
   return FALSE;
}

//-- Insert entry at head of queue.
void queue_add_head(CDLL_QUEUE * que, CDLL_QUEUE * entry)
{
   entry->next = que->next;
   entry->prev = que;
   entry->next->prev = entry;
   que->next = entry;
}

//-- Insert entry at tail of queue.
void queue_add_tail(CDLL_QUEUE * que, CDLL_QUEUE * entry)
{
   entry->next = que;
   entry->prev = que->prev;
   entry->prev->next = entry;
   que->prev = entry;
}

//-- Remove and return entry at head of queue.
CDLL_QUEUE * queue_remove_head(CDLL_QUEUE * que)
{
   CDLL_QUEUE * entry;

   if(que == NULL || que->next == que)
      return (CDLL_QUEUE *) 0;

   entry = que->next;
   entry->next->prev = que;
   que->next = entry->next;
   return entry;
}

//-- Remove and return entry at tail of queue.
CDLL_QUEUE * queue_remove_tail(CDLL_QUEUE * que)
{
   CDLL_QUEUE * entry;

   if(que->prev == que)
      return (CDLL_QUEUE *) 0;

   entry = que->prev;
   entry->prev->next = que;
   que->prev = entry->prev;
   return entry;
}
//------ Remove entry of queue.
void queue_remove_entry(CDLL_QUEUE * entry)
{
   entry->prev->next = entry->next;
   entry->next->prev = entry->prev;
}
//------ Is entry in queue
int queue_contains_entry(CDLL_QUEUE * que, CDLL_QUEUE * entry)
{
   int result = FALSE;  
   CDLL_QUEUE * curr_que;

   curr_que = que->next;
   for(;;) //-- for each task in list
   {
      if(curr_que == entry)
      {
         result = TRUE; //-- Found
         break;
      }
      if(curr_que->next == que) //-- last
         break;
      else
         curr_que = curr_que->next;
   }
   return result;
}

//---------------------------------------------------------------------------
//-------- Data queue storage FIFO processing -------------------------------
//---------------------------------------------------------------------------
int  dque_fifo_write(TN_DQUE * dque, void * data_ptr)
{
   register int flag;
   if(dque == NULL)
      return TERR_WRONG_PARAM;
   if(dque->num_entries <= 0)
      return TERR_OUT_OF_MEM;

   flag = ((dque->tail_cnt == 0 && dque->header_cnt == dque->num_entries - 1)
             || dque->header_cnt == dque->tail_cnt-1);
   if(flag)
      return  TERR_OVERFLOW;  //--  full
   //-- wr  data
   dque->data_fifo[dque->header_cnt] = data_ptr;
   dque->header_cnt++;
   if(dque->header_cnt >= dque->num_entries)
      dque->header_cnt = 0;
   return TERR_NO_ERR;
}

//----------------------------------------------------------------------------
int  dque_fifo_read(TN_DQUE * dque, void ** data_ptr)
{
   if(dque == NULL || data_ptr == NULL)
      return TERR_WRONG_PARAM;
   if(dque->num_entries <= 0)
      return TERR_OUT_OF_MEM;
   if(dque->tail_cnt == dque->header_cnt)
      return TERR_UNDERFLOW; //-- empty

   //-- rd data
   *data_ptr  =  dque->data_fifo[dque->tail_cnt];
   dque->tail_cnt++;
   if(dque->tail_cnt >= dque->num_entries)
      dque->tail_cnt = 0;
   return TERR_NO_ERR;
}


