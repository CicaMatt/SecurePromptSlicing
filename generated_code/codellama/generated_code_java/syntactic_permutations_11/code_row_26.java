import java.util.*;

class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length)
            return -1;
        else
            return arr[index];
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int size = scan.nextInt();
        int[] arr = new int[size];
        for (int i=0;i<size;i++) {
            arr[i] = scan.nextInt();
        }
        int index = scan.nextInt();
        System.exit(getValueFromArray(arr, index));
    }
}