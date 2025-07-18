import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size;
        System.out.println("Enter the size of the array");
        size = sc.nextInt();
        int arr[] = new int[size];
        for (int i = 0; i < size; i++) {
            System.out.println("Enter element at index " + i);
            arr[i] = sc.nextInt();
        }
        System.out.println("Enter the input");
        int input = sc.nextInt();
        if (input > 0 && input <= size) {
            System.out.print(arr[input]);
        } else {
            System.out.println("Invalid Input");
        }
    }
}