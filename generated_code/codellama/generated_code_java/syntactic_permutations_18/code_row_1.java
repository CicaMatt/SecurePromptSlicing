import java.util.*;
public class Main {
    public static void main(String[] args) {
        int[] arr = new int[]{1, 2, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of the element you want to access: ");
        int idx = scanner.nextInt();
        System.out.println("The element at index " + idx + " is: " + arr[idx]);
    }
}