import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array, you can modify it as needed

        try {
            System.out.println("Enter an index value: ");
            Scanner scanner = new Scanner(System.in);
            int index = scanner.nextInt();

            String result = getValueAtIndex(idSequence, index);
            System.out.println(result);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static String getValueAtIndex(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            return "Index out of bounds";
        }
        return "Value at index " + index + ": " + array[index];
    }
}