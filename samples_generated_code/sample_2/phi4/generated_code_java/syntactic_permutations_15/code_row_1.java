import java.util.Scanner;

public class ArrayIndexValue {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        int index = promptForIndex(idSequence);
        System.out.println("The value at the given index is: " + getValueAtIndex(idSequence, index));
    }

    public static int promptForIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index for the array: ");
        while (true) {
            try {
                int index = Integer.parseInt(scanner.nextLine());
                if (index >= 0 && index < idSequence.length) {
                    return index;
                } else {
                    System.out.println("Index out of bounds. Please enter a valid index between 0 and " + (idSequence.length - 1) + ": ");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter an integer: ");
            }
        }
    }

    public static int getValueAtIndex(int[] idSequence, int index) {
        return idSequence[index];
    }
}