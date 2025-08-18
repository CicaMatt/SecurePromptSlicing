import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int result = getValueAtIndex();
        System.out.println("The value at the given index is: " + result);
    }

    public static int getValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {10, 20, 30, 40, 50}; // Sample sequence

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            System.out.println("Index out of bounds.");
            return -1; // Indicating error with a sentinel value
        }
    }
}