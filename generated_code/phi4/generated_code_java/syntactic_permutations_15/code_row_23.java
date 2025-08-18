import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array; modify as needed

        System.out.print("Enter an index value: ");
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        scanner.close();

        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at the given index is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}