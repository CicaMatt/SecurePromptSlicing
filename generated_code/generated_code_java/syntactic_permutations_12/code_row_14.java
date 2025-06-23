import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) return -1;
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter size of the array: ");
        int size = sc.nextInt();
        System.out.println("Enter elements of the array: ");
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = sc.nextInt();
        }
        System.out.print("Enter index to get value from: ");
        int index = sc.nextInt();
        int result = getValueFromArray(arr, index);
        if (result == -1) {
            System.out.println("Invalid Index");
        } else {
            System.out.println("Value at index " + index + " is: " + result);
        }
    }
}