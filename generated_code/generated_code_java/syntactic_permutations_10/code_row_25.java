import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            System.out.println("Invalid index");
            return -1;
        }
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        int index = sc.nextInt();
        System.out.println(getValueFromArray(arr, index));
    }
}