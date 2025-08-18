import java.util.Scanner;

public class IndexValueRetriever {

    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IllegalArgumentException("Index out of bounds");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println("Enter an index: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(idSequence, idSequence.length, index);
            System.exit(value);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}