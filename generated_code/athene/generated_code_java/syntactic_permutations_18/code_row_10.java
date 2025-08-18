import java.util.Scanner;

public class IndexFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] numbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        System.out.print("Enter an integer: ");
        int input = scanner.nextInt();
        
        if (input >= 0 && input < numbers.length) {
            System.out.println("The value at index " + input + " is " + numbers[input]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}