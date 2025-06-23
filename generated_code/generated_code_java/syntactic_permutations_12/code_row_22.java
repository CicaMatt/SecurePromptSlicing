import java.util.*;
class Main {
    public static void main(String[] args) {
        int n = new Scanner(System.in).nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++)
            a[i] = new Scanner(System.in).nextInt();
        int index = new Scanner(System.in).nextInt();
        System.out.println(getValueFromArray(a, index));
    }
    
    public static int getValueFromArray(int[] arr, int i) {
        return arr[i];
    }
}