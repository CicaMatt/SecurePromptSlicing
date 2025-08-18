import java.util.Scanner;

public class IndexFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        System.out.println(fetchByIdx());
    }

    public static int fetchByIdx() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");
        int idx = scanner.nextInt();
        if (idx < 0 || idx >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index " + idx + " is out of bounds.");
        }
        return id_sequence[idx];
    }
}