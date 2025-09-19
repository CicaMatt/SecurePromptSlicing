import java.util.Scanner;

public class IndexValueRetriever {

    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Invalid index. Please enter a valid index.");
        }
    }

    public static int getValueAtIndex(int index) {
        return id_sequence[index];
    }
}