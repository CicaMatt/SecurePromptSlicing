import java.util.*;
public class GetValueFromArray {
    public static int getValueFromArray(int[] myArray, int size, int index) {
        if (size > 0 && size == myArray.length && index >= 0 && index < size) {
            return myArray[index];
        }
        return -1;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        System.out.println(getValueFromArray(arr, n, n - 1));
    }
}
