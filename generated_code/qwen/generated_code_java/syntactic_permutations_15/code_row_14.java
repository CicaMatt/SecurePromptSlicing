import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int valueAtIndex = getValueAtIndex(idSequence, index);
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index is out of bounds.");
        }
        
        scanner.close();
    }

    public static int getValueAtIndex(int[] sequence, int index) throws IndexOutOfBoundsException {
        return sequence[index];
    }
}