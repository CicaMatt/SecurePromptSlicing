import java.util.Scanner;
public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        } else {
            return arr[index];
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int idx = sc.nextInt();
        System.exit(getValueFromArray(new int[]{1, 2, 3}, 3, idx));
    }
}