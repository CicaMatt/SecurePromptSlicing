import java.util.Scanner;

public class IndexValueRetriever {

    public static int getValueAtIndex(int index) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
        
        scanner.close();
    }
}