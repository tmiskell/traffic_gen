#include <stdio.h>
#include <curl/curl.h>
#include "generate_traffic.h"

void* generate_traffic( void* arg ){
  CURL *curl ;
  CURLcode ret_val ;

  curl = curl_easy_init() ;

  if( curl ){
    curl_easy_setopt( curl, CURLOPT_URL, "http://localhost:8888/index.html" ) ;
    /* Tell libcurl to follow redirection */
    curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L ) ;

    /* Perform the request, and capture the return code */
    ret_val = curl_easy_perform( curl ) ;
    /* Check for errors */
    if( ret_val != CURLE_OK ){
      fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror( ret_val ) ) ;
    }
    /* Cleanup */
    curl_easy_cleanup( curl ) ;
  }
  
  return NULL ;

}
