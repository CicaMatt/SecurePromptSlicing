import java.util.Scanner;

public class IndexValueFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Error: Index out of bounds");
        }
    }

    public static int getValueAtIndex(int index) throws IndexOutOfBoundsException {
        return id_sequence[index];
    }
}