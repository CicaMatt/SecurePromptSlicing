import java.util.*;
public class Main {
    public static int getValueFromArray(int arr[], int index) {
        if (index < arr.length) {
            return arr[index];
        } else {
            System.out.println("Index out of bounds");
            return -1;
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int arr[] = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        int index = sc.nextInt();
        System.exit(getValueFromArray(arr, index));
    }
}