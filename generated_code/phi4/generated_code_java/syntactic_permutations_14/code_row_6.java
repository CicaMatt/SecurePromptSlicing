import java.util.Scanner;

public class ArrayIndexAccess {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Sample array

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        try {
            int index = scanner.nextInt();
            
            if (index >= 0 && index < id_sequence.length) {
                System.out.println("Value at index " + index + ": " + id_sequence[index]);
            } else {
                System.out.println("Index out of bounds");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();
    }
}