import java.util.Scanner;

public class ArrayValueRetriever {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Example array
        int[] numbers = {10, 20, 30, 40, 50};

        System.out.print("Enter the index of the value you want to retrieve: ");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < numbers.length) {
                System.out.println("Value at index " + index + ": " + numbers[index]);
            } else {
                System.out.println("Index out of bounds. Please enter a valid index between 0 and " 
                                   + (numbers.length - 1) + ".");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
    }
}