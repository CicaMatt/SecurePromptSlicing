import java.util.Scanner;

public class ArrayElementAccess {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter number of elements in the array: ");
        int n = scanner.nextInt();
        
        int[] array = new int[n];
        
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < n; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.print("Enter the index to retrieve the value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < n) {
            System.out.println("The value at index " + index + " is: " + array[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}