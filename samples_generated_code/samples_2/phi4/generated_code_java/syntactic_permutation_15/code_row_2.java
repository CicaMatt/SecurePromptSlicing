import java.util.Scanner;

public class ArrayIndexer {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(id_sequence));
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return -1; // or handle error as appropriate
        }
        
        if (index < 0 || index >= idSequence.length) {
            System.out.println("Index out of bounds.");
            return -1; // or handle error as appropriate
        }

        return idSequence[index];
    }
}