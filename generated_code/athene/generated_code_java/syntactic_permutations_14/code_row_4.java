import java.util.Scanner;

public class IndexFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        System.out.println(fetchValueAtGivenIndex());
    }

    public static int fetchValueAtGivenIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
        return id_sequence[index];
    }
}