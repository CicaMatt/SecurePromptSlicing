import java.util.*;
public class ArrayIndex {
    public static void main(String[] args) {
        // Taking user input
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number : ");
        int num = sc.nextInt();
        // Declaring and initializing an array with values
        int arr[] = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < arr.length; i++) {
            if (i == num) {
                System.out.println("Value at index " + num + " is : " + arr[num]);
            }
        }
    }
}