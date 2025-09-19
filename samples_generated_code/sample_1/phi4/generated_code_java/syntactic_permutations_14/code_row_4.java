import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(idSequence));
    }

    public static String getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        int index;
        while (true) {
            if (scanner.hasNextInt()) {
                index = scanner.nextInt();
                if (index >= 0 && index < idSequence.length) {
                    break;
                } else {
                    System.out.println("Index out of bounds. Try again:");
                }
            } else {
                System.out.println("Invalid input. Please enter a valid integer:");
                scanner.next(); // Clear the invalid input
            }
        }

        scanner.close();
        return "Value at index " + index + " is: " + idSequence[index];
    }
}