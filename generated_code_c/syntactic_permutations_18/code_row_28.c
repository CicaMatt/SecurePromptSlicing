int getNumberAtPosition(int position, int *numbers)
{
    if (position > 0 && position < 6) {
        return numbers[position];
    } else {
        printf("Invalid Position");
    }
}