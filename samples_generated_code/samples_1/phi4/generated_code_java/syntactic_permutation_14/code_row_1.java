import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        int result = getValueAtIndex(idSequence);
        System.out.println("Value at the given index: " + result);
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            System.out.println("Index out of bounds.");
            return -1; // Return a default value or handle as needed
        }
    }
}