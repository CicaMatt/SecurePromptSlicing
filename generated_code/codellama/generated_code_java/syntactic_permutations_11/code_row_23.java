import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int idx) {
        if (idx >= 0 && idx < arr.length) {
            return arr[idx];
        } else {
            throw new ArrayIndexOutOfBoundsException();
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int idx = scanner.nextInt();
        System.exit(getValueFromArray(args, idx));
    }
}