import java.util.*;

public class Main {
    public static void main(String[] args) {
        int[] arr = new int[5];
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int x = scanner.nextInt();
        getValueFromArray(arr, 5, x);
    }

    public static void getValueFromArray(int[] arr, int size, int index) {
        System.out.println(arr[index]);
    }
}