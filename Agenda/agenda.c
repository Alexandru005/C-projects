#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define SIZE 100
#define LINE_SIZE 256

typedef enum{
  January = 1,
  February,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November,
  December
}month_t;

typedef struct{

  unsigned int year : 16;
  unsigned int day : 5;
  unsigned int hour : 5;
  char title[25];
  char detail[50];
  month_t month;

}eveniment_t;

eveniment_t* extract_data(eveniment_t *e, int *space, int *nr, FILE *f)
{

  char line[LINE_SIZE];
  char *word;

  
  while(fgets(line, LINE_SIZE, f))// extracting info line by line 
    {

      if(*nr + 1 == *space) // realloc space if it needs one more space
	{
	  e = realloc(e, *space + SIZE * (1 * sizeof(eveniment_t)));
	  if(e == NULL)
	    {
	      perror("Realloc failed");
	    }
	  *space = *space + SIZE * (1 * sizeof(eveniment_t));
	}

      word = strtok(line, ":");
      int i = 1;
      int aux;

      while(word != NULL)
	{
	  switch(i)
	    {
	    case 1:

	      aux = atoi(word);
	      e[*nr].year = aux;
	      
	      break;

	    case 2:

	      aux = atoi(word);
	      e[*nr].month = aux;
	      
	      break;

	    case 3:

	      aux = atoi(word);
	      e[*nr].day = aux;
	      
	      break;

	    case 4:

	      aux = atoi(word);
	      e[*nr].hour = aux;
	      
	      break;

	    case 5:

	      strcpy(e[*nr].title, word);
	      
	      break;

	    case 6:

	      strcpy(e[*nr].detail, word);
	      
	      break;
	    }
	  i++;
          word = strtok(NULL, ":");
	}
      (*nr)++;
    }

  
  return e;
}

void display_eveniments(eveniment_t *e, int nr)
{
  for(int i = 0; i < nr; i++)
    printf("%d:%d:%d:%d:%s:%s", e[i].year,  e[i].month,  e[i].day,  e[i].hour,  e[i].title,  e[i].detail);
}

eveniment_t* read_eveniment(eveniment_t *e)
{
  
  int aux;
  printf("year:");
  scanf("%d", &aux);
  e->year = aux;

  printf("month:");
  scanf("%d", &aux);
  e->month = aux;

  printf("day:");
  scanf("%d", &aux);
  e->day = aux;

  printf("hour:");
  scanf("%d", &aux);
  e->hour = aux;

  getchar();

  printf("title:");
  fgets(e->title, sizeof(e->title), stdin);
  e->title[strcspn(e->title, "\n")] = 0;

  printf("details:");
  fgets(e->detail, sizeof(e->detail), stdin);

  return e;
}

void display_new_eveniment(eveniment_t e)
{
    printf("%d:%d:%d:%d:%s:%s\n", e.year,  e.month,   e.day,  e.hour,   e.title,   e.detail);
}

int search(eveniment_t new, eveniment_t *old, int nr)
{
  for(int i = 0 ;i < nr; i++)
    {
      if(new.year == old[i].year)
	if(new.month == old[i].month)
	  if(new.day == old[i].day)
	    if(new.hour == old[i].hour)
	      return i;
    }
  
  return -1;
}

eveniment_t* add(eveniment_t *old, eveniment_t new, int *nr, int *space)
{
  if(*nr + 1 == *space) // realloc space if it needs one more space
    {
      old = realloc(old, *space + SIZE * (1 * sizeof(eveniment_t)));
      if(old == NULL)
	{
	  perror("Realloc failed");
	}
      *space = *space + SIZE * (1 * sizeof(eveniment_t));
    }
  
  old[*nr].year = new.year; 
  old[*nr].month = new.month;
  old[*nr].day = new.day;
  old[*nr].hour = new.hour;
  strcpy(old[*nr].title,new.title);
  strcpy(old[*nr].detail,new.detail);

  *nr = *nr + 1;
       
  return old;
}

void add_data_in_file(FILE *f, eveniment_t *e, int nr)
{
   for(int i = 0; i < nr; i++)
     fprintf(f, "%d:%d:%d:%d:%s:%s", e[i].year,  e[i].month,  e[i].day,  e[i].hour,  e[i].title,  e[i].detail);
  
}

int compare_events(const void *a, const void *b)
{
    const eveniment_t *e1 = (const eveniment_t *)a;
    const eveniment_t *e2 = (const eveniment_t *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    if (e1->month != e2->month)
        return e1->month - e2->month;

    if (e1->day != e2->day)
        return e1->day - e2->day;

    return e1->hour - e2->hour;
}

eveniment_t* read_date(eveniment_t *e)
{
  
  int aux;
  printf("year:");
  scanf("%d", &aux);
  e->year = aux;

  printf("month:");
  scanf("%d", &aux);
  e->month = aux;

  printf("day:");
  scanf("%d", &aux);
  e->day = aux;

  printf("hour:");
  scanf("%d", &aux);
  e->hour = aux;

  return e;
}

eveniment_t* delete(eveniment_t *old, int *nr, int poz)
{

  for(int i = poz; i < *nr - 1; i++)
    {
      old[i].year =  old[i+1].year; 
      old[i].month = old[i+1].month;
      old[i].day = old[i+1].day;
      old[i].hour =  old[i+1].hour;
      strcpy(old[i].title, old[i+1].title);
      strcpy(old[i].detail, old[i+1].detail);
    }

  *nr = *nr - 1;

  return old;
}


int main()
{
  
  FILE *f = fopen("Info.txt", "r"); // open file to extract data

  if(f == NULL)
    {
      perror("Error open file");
    }

  eveniment_t *old = malloc(SIZE * sizeof(eveniment_t));

  if(old == NULL)
    {
      perror("Alloc failed");
    }

  int space_alloc = SIZE * sizeof(eveniment_t);
  int nr_elements = 0;
  
  old = extract_data(old, &space_alloc, &nr_elements, f); // extracting data from file
  //display_eveniments(old, nr_elements); // verify if we save corect data
  
  fclose(f);

  f = fopen("Info.txt", "w");// open file to write new data

  uint8_t op;
  eveniment_t new;

  do{
    printf("Menu\n");
    printf("0 - exit menu\n");
    printf("1 - read new eveniment\n");
    printf("2 - delete eveniment\n");
    printf("insert option:");
    scanf("%hhd", &op);
    printf("===========================\n");

    switch(op)
      {
      case 1:
	read_eveniment(&new);
	//display_new_eveniment(new); // verify if we save corect data

	if(search(new,old,nr_elements) == -1) // verify if the date is free
	  {
	    old = add(old, new, &nr_elements, &space_alloc); // add the new eveniment
	    //display_eveniments(old, nr_elements); // verify the new list
	    printf("The eveniment was added\n");
	  }
	else
	  {
	    printf("An eveniment it is already existing\n");
	  }
	break;

      case 2:
	read_date(&new);
	int poz;
	if((poz = search(new,old,nr_elements)) != -1) // we found what we want to delete
	  {
	    old = delete(old, &nr_elements, poz); // delete the eveniment
	    //display_eveniments(old, nr_elements); // verify the new list
	    printf("The eveniment was deleted\n");
	  }
	else
	  {
	    printf("The eveniment introduced it's not here\n");
	  }
	break;
      }
    printf("\n");
    
  }while(op != 0);

  qsort(old, nr_elements, sizeof(eveniment_t), compare_events);
  add_data_in_file(f, old, nr_elements);

  fclose(f);

  return 0;
}
