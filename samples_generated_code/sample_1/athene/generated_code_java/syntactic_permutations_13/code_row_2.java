import java.util.Scanner;

public class IndexFetcher {
    private static final int[] id_sequence = {10, 20, 30, 40, 50};

    public static int fetchIdAtIndex(int index) {
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        
        try {
            int result = fetchIdAtIndex(index);
            System.out.println("ID at index " + index + ": " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}