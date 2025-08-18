import java.util.Scanner;

public class IndexValueFetcher {

    public static int getValueAtIndex(int index) {
        int[] values = {10, 20, 30, 40, 50};
        if (index >= 0 && index < values.length) {
            return values[index];
        } else {
            throw new IndexOutOfBoundsException("Index is out of bounds");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        try {
            int value = getValueAtIndex(index);
            System.out.println("The value at index " + index + " is: " + value);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
        
        scanner.close();
    }
}