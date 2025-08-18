import java.util.Scanner;

public class IdSequenceAccessor {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(idSequence));
    }

    public static Integer getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            return null; // Or handle error appropriately
        }

        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            System.out.println("Index out of bounds. Please enter an index between 0 and " + (idSequence.length - 1));
            return null; // Or handle error appropriately
        }
    }
}