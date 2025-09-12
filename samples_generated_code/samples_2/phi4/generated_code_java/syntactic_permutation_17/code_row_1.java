import java.util.Scanner;

public class ArrayValueRetriever {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the number of elements in the array: ");
        int size = scanner.nextInt();
        
        int[] array = new int[size];
        
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.print("Enter the index to retrieve: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < size) {
            System.out.println("Value at index " + index + ": " + array[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}