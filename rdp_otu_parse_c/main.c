#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "parse_files.h"
#include "rep_seq.h"
#include "microbiome.h"
/*

Sanjeev Sariya
Date 11 March 2016
Price Lab, 450 New Hampshire NW Ave

gcc -g -Wall -Wextra *.c -o program_parse -pedantic -std=gnu99

gcc -g -Wall -Wextra -pedantic *.c -o parse 

gcc -g -Wall -Wextra -pedantic *.c -o parse  -std=c99

- Cannot use -pedantic while compiling as it mixes
- Canot use -std=c99 it conflicts with unistd
*/

void print_help();

int main(int argc, char *argv[]){
  
  if(argc == 1){
    print_help();
    return 0;/*EXIT*/
  }
  char get_opt;
  const char *rdp_file=NULL; /*rdp file*/
  const char *map_file=NULL; /*otu-map file*/
  const char *run_name=NULL; /*output prefix file name*/
  float confid=0.8; /*conf while parsing RDP output*/

  while((get_opt=getopt(argc, argv,"n:r:c:m:")) !=-1){
    
    switch(get_opt){
    case 'r':
      rdp_file=optarg;
      break;
    case 'c':
      confid=atof(optarg);/*convert to float*/
      break;
    case 'm':
      map_file=optarg;
      break;
    case 'n':
      run_name=optarg;
      break;
    case '?':
      print_help();
      /*anything else - break and print help*/
      break;
    }
    /*switch case ends*/
  }/*while ends*/
    
  struct Rep_seq *head_rep =parse_otu_map_file(map_file);
  struct Microbiome *head_microb=parse_rdp_file(rdp_file);
  if(head_rep!=NULL){
    
    print_list(head_rep);

  }else{
    printf("Memory issues to main rep-seq node\n");
  }
  delete_rep_node(&head_rep);

  return 0;
}
// main ends----------
void print_help(){
  
  printf("parse -c <confidence> -r <rdp output> -n <run_name> -m <otu-map file>\n");
  printf("-c confidence threshold\n");
  printf("-r RDP file output\n");
  printf("-n run name\n");
  printf("-m otu-map\n");
  
}
//-- function ends--
