import java.util.Scanner;

public class GetValueFromArray {
    public static int getValueFromArray(int[] arr, int index) {
        if (index > -1 && index < arr.length) {
            return arr[index];
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the size of array: ");
        int n = scanner.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }
        System.out.println("Enter the index: ");
        int idx = scanner.nextInt();
        System.exit(getValueFromArray(arr, idx));
    }
}