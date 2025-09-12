import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array

        try {
            System.out.println("Value at the index: " + getValueAtIndex(idSequence));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] idSequence) throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index < 0 || index >= idSequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds.");
        }

        return idSequence[index];
    }
}