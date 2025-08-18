import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int valueAtIndex = getValueAtIndex(id_sequence, index);
            System.out.println("Value at index " + index + ": " + valueAtIndex);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index is out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] array, int index) throws IndexOutOfBoundsException {
        return array[index];
    }
}