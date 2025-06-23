import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = {1024, 576, 894, 349, 23, 178};
        
        System.exit(getValueFromArray(id_sequence, scanner.nextInt()));
    }
}

### Explanation:
- First, we imported the Scanner class from the java.util package to read input from the standard input.
- We then defined a method called getValueFromArray that takes an array of integers and an index as its parameters and returns the value at the given index in the array.
- Finally, we defined the main method which reads an integer from the standard input and calls the getValueFromArray method with the id_sequence array; its size and the read integer. The return value of getValueFromArray is returned as the exit code of the program using System.exit() function.