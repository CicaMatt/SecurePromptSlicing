import java.util.Scanner;

public class IndexValueFetcher {

    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAt(id_sequence, index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAt(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return array[index];
    }
}