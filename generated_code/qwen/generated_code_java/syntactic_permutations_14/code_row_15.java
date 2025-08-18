import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please enter a valid index.");
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] idSequence, int index) throws IndexOutOfBoundsException {
        return idSequence[index];
    }
}