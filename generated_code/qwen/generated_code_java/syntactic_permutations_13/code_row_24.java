import java.util.Scanner;

public class ArrayIndexValue {

    public static int getValueAtIndex(int[] idSequence, int index) {
        if (index < 0 || index >= idSequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return idSequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] idSequence = {10, 20, 30, 40, 50};

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            int value = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}