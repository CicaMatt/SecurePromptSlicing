import java.util.Scanner;

public class ArrayIndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter the size of the array:");
        int size = scanner.nextInt();
        int[] array = new int[size];
        
        System.out.println("Enter " + size + " elements for the array:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.println("Enter the index to retrieve the value from the array:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < size) {
            System.out.println("The value at index " + index + " is: " + array[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}