import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + ": " + numbers[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}