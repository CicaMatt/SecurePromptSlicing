import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        System.out.println(getValueAtIndex(arr, n, sc.nextInt()));
    }
    public static int getValueAtIndex(int[] arr, int size, int index) {
        return arr[index];
    }
}