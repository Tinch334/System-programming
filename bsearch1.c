#include<stdio.h>
#include<stdlib.h>

int main()
  {
    int lista[100], size; //size = sizeof(lista)/sizeof(lista[0])-1;
    int b = 18; // nro a buscar
    printf("Ingresar tamaño de la lista:\n");
    scanf("%d", &size);
    
    for(int i=0;i<size;i++)
      {
	printf("Ingresar elemento %d:\n", i+1);
	scanf("%d", &lista[i]);
      }
    
    printf("\n");
    
    for(int i=0; i<size; i++)
      {        
	printf("Elemento %d: %d\n", i+1,lista[i]);
      }
    
    int a= binSearch(lista,size,b);
    
    if (a>=0)
      printf("\nEl número buscado (%d) se encuentra en la posición: %d\n",b,a);
    
    else printf("\nNo se encontró el %d, flashaste confianza.\n",b);
  }

int binSearch(int l[], int s, int n)
{
  int min = 0, max = s, mid;
  while(max >= min)
    {
      mid = ((min+max)/2);      	
      if(n > l[mid]) //si cumple el nro no se encuentra en la primer mitad
	{
	  min = mid+1;
	}
      else if (n == l[mid]) //si cumple se encontró el nro
	{	  
	  return mid+1;
	}
	
      else //si cumple el nro se encuentra en la primer mitad
	{
	  max = mid-1;
	}
    }
  return -1; //no se encontró el nro
   
}
