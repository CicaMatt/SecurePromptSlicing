import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int idx = sc.nextInt();
        String [] arr = new String[]{"a", "b", "c"};
        System.out.println(getValue(arr, idx));
    }
    
    public static String getValue(String [] arr, int idx) {
        return arr[idx];
    }
}