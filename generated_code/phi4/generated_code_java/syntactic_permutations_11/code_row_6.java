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
        int inputIndex = scanner.nextInt();
        
        int idSequence[] = {1, 2, 3, 4, 5}; // Example array
        int size = idSequence.length;

        try {
            int result = getValueAtIndex(idSequence, size, inputIndex);
            System.exit(result);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }
}