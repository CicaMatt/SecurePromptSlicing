import java.util.Scanner;

public class IndexValueRetriever {

    public static String getValueAtIndex(int index) {
        String[] values = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};
        if (index >= 0 && index < values.length) {
            return values[index];
        } else {
            return "Index out of bounds";
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        String result = getValueAtIndex(index);
        System.out.println("Value at index " + index + ": " + result);
        scanner.close();
    }
}