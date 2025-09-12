import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Define an example array
        int[] exampleArray = {10, 20, 30, 40, 50};

        System.out.println("Enter the index of the value you want to retrieve:");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());

            if (index >= 0 && index < exampleArray.length) {
                System.out.println("Value at index " + index + ": " + exampleArray[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer value for the index.");
        }

        scanner.close();
    }
}