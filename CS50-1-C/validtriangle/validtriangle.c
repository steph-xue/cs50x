// The 'validtriangle' program allows the user to input 3 lengths of a tringle and tells the user if it would make a valid triangle
// A triangle is valid if all sides are positive (>0) and the sum of the lengths of 2 sides is not less than the length of the 3rd side

#include <cs50.h>
#include <stdio.h>

bool validtriangle(float x, float y, float z);

int main(void)
{
    // Gets the user to input 3 lengths for a triangle
    float x = get_float("What is the length of the 1st side of the triangle?: ");
    float y = get_float("What is the length of the 2nd side of the triangle?: ");
    float z = get_float("What is the length of the 3rd side of the triangle?: ");

    // Determines if the triangle is valid and prints if it is a valid or invalid triangle
    if (validtriangle(x, y, z))
    {
        printf("Valid triangle\n");
    }
    else
    {
        printf("Invalid triangle\n");
    }
}


// Determines if the triangle is valid (positive sides and the sum of the lengths of 2 sides is not less than the length of the 3rd side)
bool validtriangle(float x, float y, float z)
{
    // If any side is not positive (<1), then it is not a valid triangle
    if (x < 1 || y < 1 || z < 1)
    {
        return false;
    }

    // If any sum of the lengths of 2 sides is less than the length of the 3rd side, then it is not a valid triangle
    if ((x + y) < z || (x + z) < y || (y + z) < x)
    {
        return false;
    }

    else
    {
        return true;
    }
}
