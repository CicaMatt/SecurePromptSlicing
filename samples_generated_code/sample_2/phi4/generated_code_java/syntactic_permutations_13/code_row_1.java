import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int dex = scanner.nextInt();
        scanner.close();

        try {
            int result = getValueAtIndex(id_sequence, dex);
            System.out.println("Value at the given index: " + result);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] array, int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        }
        return array[index];
    }
}