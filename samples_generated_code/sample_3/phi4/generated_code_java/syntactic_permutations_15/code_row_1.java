import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(idSequence));
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index;
        
        try {
            index = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return -1; // Return an error code or handle as appropriate
        }
        
        if (index < 0 || index >= idSequence.length) {
            System.out.println("Index out of bounds.");
            return -1; // Return an error code or handle as appropriate
        }

        return idSequence[index];
    }
}