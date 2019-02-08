#include <pthread.h>
#include <stdio.h>
#include "generate_traffic.h"
#include "collect_data.h"

int main( int argc, char* argv[] ){

  int i ;
  int num_tg_threads = 1 ;
  int num_dc_threads = 1 ;
  pthread_t tg_threads[1] ;
  pthread_t dc_threads[1] ;
  pthread_attr_t tg_attrs[1] ;
  pthread_attr_t dc_attrs[1] ;
  
  /* Parse arguments */

  /* Create traffic generator threads */
  for( i = 0 ; i < num_tg_threads ; i++ ){
    pthread_create( &tg_threads[i], NULL, generate_traffic, NULL ) ;
  }

  /* Create data collection threads */
  for( i = 0 ; i < num_dc_threads ; i++ ){
    pthread_create( &dc_threads[i], NULL, collect_data, NULL ) ;    
  }

  /* Join on traffic generator threads */
  for( i = 0 ; i < num_tg_threads ; i++ ){
    pthread_join( tg_threads[i], NULL ) ;    
  }

  /* Join on data collection threads */
  for( i = 0 ; i < num_dc_threads ; i++ ){
    pthread_join( dc_threads[i], NULL ) ;    
  }

  /* Finalize results */

  /* Output results */

  /* Clean up */
  
  return 0 ;
  
}