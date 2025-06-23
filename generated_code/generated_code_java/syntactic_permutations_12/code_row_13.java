import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index > 0 && index < arr.length) {
            return arr[index];
        } else {
            return -1;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int n = sc.nextInt();
        int[] arr = {1, 2, 3, 4, 5};
        System.exit(getValueFromArray(arr, n));
    }
}