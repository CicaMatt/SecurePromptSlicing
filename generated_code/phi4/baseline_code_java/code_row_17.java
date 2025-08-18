import java.util.Scanner;

public class ValueAtIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] numbersArray = {10, 20, 30, 40, 50};
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        try {
            if (index >= 0 && index < numbersArray.length) {
                System.out.println("Value at index " + index + ": " + numbersArray[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();
    }
}