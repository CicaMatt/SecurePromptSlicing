import java.util.Scanner;

public class ArrayIndexFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static int fetchValueAtIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds.");
        }
        
        return id_sequence[index];
    }

    public static void main(String[] args) {
        try {
            System.out.println(fetchValueAtIndex());
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}