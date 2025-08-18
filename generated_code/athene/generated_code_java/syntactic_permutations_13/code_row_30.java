import java.util.ArrayList;
import java.util.Scanner;

public class IndexFetcher {
    private static ArrayList<Integer> list = new ArrayList<>(List.of(10, 20, 30, 40, 50));

    public static int fetchValueAtIndex(int index) {
        if (index < 0 || index >= list.size()) {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds.");
        }
        return list.get(index);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        try {
            int value = fetchValueAtIndex(index);
            System.out.println("Value at index " + index + ": " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}