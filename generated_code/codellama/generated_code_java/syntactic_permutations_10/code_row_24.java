import java.util.*;

public class Main {
    public static int getValue(int[] arr, int index) {
        if (arr == null || arr.length == 0 || index < 0 || index >= arr.length) {
            return -1;
        } else {
            return arr[index];
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int index = sc.nextInt();
        int[] id_sequence = {1, 2, 3, 4};
        System.out.println(getValue(id_sequence, index));
    }
}