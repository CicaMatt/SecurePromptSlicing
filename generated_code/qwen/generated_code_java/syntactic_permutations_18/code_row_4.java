import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < numbers.length) {
            System.out.println("Value at index " + index + ": " + numbers[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}