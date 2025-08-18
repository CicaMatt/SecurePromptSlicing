import java.util.Scanner;

public class IdSequenceLookup {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(id_sequence));
    }

    public static Integer getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index value: ");
        
        int index = -1;
        try {
            index = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return null; // or handle as needed
        }
        
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            System.out.println("Index out of bounds.");
            return null; // or handle as needed
        }
    }
}