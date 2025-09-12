import java.util.Scanner;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        String[] elements = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index (0-4): ");
        
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
            if (index >= 0 && index < elements.length) {
                System.out.println("Element at index " + index + ": " + elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid integer.");
        }
        
        scanner.close();
    }
}