import java.util.Scanner;

public class IndexFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        String result = getValueAtIndex(index);
        System.out.println("Value at index " + index + ": " + result);
        scanner.close();
    }

    public static String getValueAtIndex(int index) {
        String[] values = {"apple", "banana", "cherry", "date", "elderberry"};
        if (index < 0 || index >= values.length) {
            return "Index out of bounds";
        }
        return values[index];
    }
}