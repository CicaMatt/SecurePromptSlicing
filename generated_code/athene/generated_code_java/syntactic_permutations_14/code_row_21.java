import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        System.out.println(fetchValueAtIndex(id_sequence));
    }

    public static int fetchValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new ArrayIndexOutOfBoundsException("Index is out of bounds");
        }
        return id_sequence[index];
    }
}