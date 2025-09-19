import java.util.Scanner;

public class ArrayValueFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] values = {10, 20, 30, 40, 50};
        
        System.out.print("Enter a number (index): ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < values.length) {
            System.out.println("Value at index " + index + ": " + values[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}