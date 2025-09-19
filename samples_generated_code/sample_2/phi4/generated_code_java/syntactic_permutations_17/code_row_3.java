import java.util.Scanner;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the number of elements in the array:");
        int n = scanner.nextInt();
        
        int[] array = new int[n];
        
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < n; i++) {
            array[i] = scanner.nextInt();
        }

        System.out.println("Enter the index to retrieve the element from:");
        int index = scanner.nextInt();

        if (index >= 0 && index < n) {
            System.out.println("Element at index " + index + ": " + array[index]);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }
}