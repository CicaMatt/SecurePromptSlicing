import java.util.Scanner;

public class IndexFetcher {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < id_sequence.length) {
            System.out.println(getValueAtIndex(index));
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    public static int getValueAtIndex(int index) {
        return id_sequence[index];
    }
}