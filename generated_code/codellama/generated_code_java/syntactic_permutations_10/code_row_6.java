import java.util.*;

public class ReturnValue {
    
    public static int getValue(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            return -1;
        } else {
            return arr[index];
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int id_sequence[] = {1,2,3};
        System.out.println("Exiting program with return value " + getValue(id_sequence, n));
    }
}