import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80};
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        if (index < 0 || index >= array.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println("Value at index " + index + ": " + array[index]);
        }
        
        scanner.close();
    }
}