import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int index = promptForIndex();
        System.out.println("The value at index " + index + " is: " + getValueAtIndex(index));
    }

    private static int promptForIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        while (!scanner.hasNextInt()) {
            System.out.println("That's not a valid integer. Please enter an integer.");
            scanner.next(); // discard invalid input
        }
        return scanner.nextInt();
    }

    private static int getValueAtIndex(int index) {
        int[] id_sequence = {10, 20, 30, 40, 50, 60};
        
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            System.out.println("Index out of bounds. Returning -1.");
            return -1;
        }
    }
}