import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example sequence

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();

        try {
            int result = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] idSequence, int index) {
        if (index < 0 || index >= idSequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
        return idSequence[index];
    }
}