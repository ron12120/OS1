#include <stdio.h>


void infinte_recursion(int n)
{
    infinte_recursion(n+1);
}


int main()
{
    infinte_recursion(0);
    return 0;
}