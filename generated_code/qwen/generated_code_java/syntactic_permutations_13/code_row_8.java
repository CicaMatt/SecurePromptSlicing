import java.util.Scanner;

public class IndexValueRetriever {

    public static int getValueAtIndex(int index, int[] idSequence) {
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            throw new IllegalArgumentException("Index out of bounds");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] idSequence = {10, 20, 30, 40, 50};

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(index, idSequence);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}