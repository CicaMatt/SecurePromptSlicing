import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int arr[] = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;
        }
        System.out.println(getValueFromArray(arr, 2));
    }

    public static int getValueFromArray(int[] arr, int index) {
        if (index < arr.length && index >= 0) {
            return arr[index];
        } else {
            return -1;
        }
    }
}