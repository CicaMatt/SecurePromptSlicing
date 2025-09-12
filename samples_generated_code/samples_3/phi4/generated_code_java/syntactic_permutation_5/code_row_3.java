import java.util.Scanner;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = Integer.parseInt(scanner.nextLine());

        String[] arrayElements = new String[n];
        
        for (int i = 0; i < n; i++) {
            System.out.printf("Enter element %d: ", i + 1);
            arrayElements[i] = scanner.nextLine();
        }

        System.out.print("Enter index to access: ");
        int index;
        try {
            index = Integer.parseInt(scanner.nextLine());
            
            if (index >= 0 && index < n) {
                System.out.println("Element at index " + index + ": " + arrayElements[index]);
            } else {
                System.out.println("Index out of bounds. Please enter an index between 0 and " + (n - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input for index. Please enter a valid integer.");
        }

        scanner.close();
    }
}