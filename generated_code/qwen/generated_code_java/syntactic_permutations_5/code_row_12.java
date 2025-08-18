import java.util.Scanner;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"zero", "one", "two", "three", "four"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index (0 to 4): ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < elements.length) {
            System.out.println("Element at index " + index + ": " + elements[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}