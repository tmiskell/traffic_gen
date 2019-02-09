#include <pthread.h>
#include <stdio.h>
#include <curl/curl.h>
#include "generate_traffic.h"
#include "collect_data.h"
#include "generate_logs.h"

int main( int argc, char* argv[] ){

  int i ;
  int num_tg_threads = 1 ;
  int num_dc_threads = 1 ;
  int num_lg_threads = 1 ;
  pthread_t tg_threads[1] ;
  pthread_t dc_threads[1] ;
  pthread_t lg_threads[1] ;
  pthread_attr_t tg_attrs[1] ;
  pthread_attr_t dc_attrs[1] ;
  pthread_attr_t lg_attrs[1] ;
  int ret_val ;
  
  /* Parse arguments */

  /* Perform initialization */
  curl_global_init( CURL_GLOBAL_ALL ) ;
  
  /* Create logging threads */
  for( i = 0 ; i < num_lg_threads ; i++ ){
    ret_val = pthread_create( &lg_threads[i], NULL, generate_logs, NULL ) ;
    if( ret_val != 0 ){
      fprintf( stderr, "Unable to generate logging thread number %d, error: %d", i+1, ret_val ) ;
    }
  }

    /* Create data collection threads */
  for( i = 0 ; i < num_dc_threads ; i++ ){
    ret_val = pthread_create( &dc_threads[i], NULL, collect_data, NULL ) ;    
    if( ret_val != 0 ){
      fprintf( stderr, "Unable to generate data collection thread number %d, error: %d", i+1, ret_val ) ;
    }
  }
  
  /* Create traffic generator threads */
  for( i = 0 ; i < num_tg_threads ; i++ ){
    ret_val = pthread_create( &tg_threads[i], NULL, generate_traffic, NULL ) ;
    if( ret_val != 0 ){
      fprintf( stderr, "Unable to generate traffic generator thread number %d, error: %d", i+1, ret_val ) ;
    }
  }

  /* Signal traffic generator threads to start */
  /* Signal data collection threads to start */

  /* Join on traffic generator threads */
  for( i = 0 ; i < num_tg_threads ; i++ ){
    ret_val = pthread_join( tg_threads[i], NULL ) ;
  }

  /* Join on data collection threads */
  for( i = 0 ; i < num_dc_threads ; i++ ){
    ret_val = pthread_join( dc_threads[i], NULL ) ;    
  }

  /* Join on logging threads */
  for( i = 0 ; i < num_lg_threads ; i++ ){
    ret_val = pthread_join( lg_threads[i], NULL ) ;    
  }
  
  /* Finalize results */

  /* Output results */

  /* Clean up */
  
  return 0 ;
  
}
