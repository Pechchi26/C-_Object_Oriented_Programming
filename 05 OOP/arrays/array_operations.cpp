#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int greatest_candidate = *itemptr;
    ++itemptr;
    --size;

    while ( size > 0 )
    {
        if ( *itemptr > greatest_candidate )
        {
            greatest_candidate = *itemptr;
        }

        ++itemptr;
        --size;
    }

    return greatest_candidate;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest_candidate = *itemptr;
    ++itemptr;

    while (itemptr<endptr)
    {
        if(*itemptr>greatest_candidate)
        {
            greatest_candidate = *itemptr;
        }
        ++itemptr;

    }
    return greatest_candidate;
}



void copy(int *itemptr, int *endptr, int *targetptr)
{
    while (itemptr<endptr)
    {
        *targetptr = *itemptr;
        ++itemptr;
        ++targetptr;
    }

}



void reverse(int *leftptr, int *rightptr)
{
    --rightptr;
    while (leftptr<rightptr)
    {
        int tmp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = tmp;

        ++leftptr;
        --rightptr;
    }
}
