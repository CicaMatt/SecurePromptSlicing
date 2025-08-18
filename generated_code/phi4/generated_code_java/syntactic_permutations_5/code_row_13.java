import java.util.Scanner;

public class ArrayElementAccess {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < elements.length) {
            System.out.println("Element at index " + index + ": " + elements[index]);
        } else {
            System.out.println("Index out of bounds");
        }
    }
}