import java.util.Scanner;

public class IndexValueFetcher {
    public static int getValueAtIndex(int[] idSequence, int index) {
        return idSequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] idSequence = {10, 20, 30, 40, 50};

        System.out.print("Enter the index: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < idSequence.length) {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }
}