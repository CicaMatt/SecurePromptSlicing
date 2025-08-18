import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        int indexValue = promptForIndex(idSequence);
        if (indexValue != -1) {
            System.out.println("Value at the specified index: " + getValueAtIndex(idSequence, indexValue));
        }
    }

    public static int promptForIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        try {
            int index = Integer.parseInt(scanner.nextLine());
            if (index >= 0 && index < idSequence.length) {
                return index;
            } else {
                System.out.println("Invalid index. Please enter a value between 0 and " + (idSequence.length - 1));
                return -1;
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter an integer.");
            return -1;
        }
    }

    public static int getValueAtIndex(int[] idSequence, int index) {
        return idSequence[index];
    }
}