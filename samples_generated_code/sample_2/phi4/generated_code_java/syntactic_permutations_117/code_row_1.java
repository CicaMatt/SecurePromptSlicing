import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int[] arr = {10, 20, 30};
        
        String str_a = convertToString(arr[0]);
        String str_b = convertToString(arr[1]);
        String str_c = convertToString(arr[2]);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToString(int number) {
        return Integer.toString(number);
    }
}