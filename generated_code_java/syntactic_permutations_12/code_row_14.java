import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] arr = {1, 2, 3};
        System.exit(getValueFromArray(arr, scanner.nextInt()));
    }
}