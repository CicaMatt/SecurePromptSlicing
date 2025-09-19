import java.util.Scanner;

public class IndexValueRetriever {

    private static final int[] idSequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        System.out.print("Enter an index value: ");
        Scanner scanner = new Scanner(System.in);
        
        try {
            int index = scanner.nextInt();
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (Exception e) {
            System.out.println("Invalid input or index out of bounds.");
        } finally {
            scanner.close();
        }
    }

    public static int getValueAtIndex(int index) {
        if (index < 0 || index >= idSequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return idSequence[index];
    }
}