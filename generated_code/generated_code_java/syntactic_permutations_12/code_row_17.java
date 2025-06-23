import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        int size = Integer.parseInt(sc.nextLine());
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = Integer.parseInt(sc.nextLine());
        }

        System.exit(getValueFromArray(arr, Integer.parseInt(sc.nextLine())));
    }

    public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }
}