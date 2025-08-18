import java.util.Scanner;

public class IndexValueFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < id_sequence.length) {
            System.out.println("Value at index " + index + ": " + id_sequence[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}