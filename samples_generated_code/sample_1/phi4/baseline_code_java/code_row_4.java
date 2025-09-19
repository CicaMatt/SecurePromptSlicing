import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

        System.out.println("Enter the index of the element you want to retrieve:");
        
        try {
            int index = scanner.nextInt();
            
            if (index >= 0 && index < array.length) {
                System.out.println("Value at index " + index + ": " + array[index]);
            } else {
                System.out.println("Index out of bounds. Please enter an index between 0 and " 
                                   + (array.length - 1) + ".");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        scanner.close();
    }
}