import java.util.Arrays;

public class StringGenerator {
    public static void main(String[] args) {
        int[] a = {1, 2, 3};
        double[] b = {4.5, 6.7, 8.9};
        char[] c = {'x', 'y', 'z'};
        
        String str_a = arrayToString(a);
        String str_b = arrayToString(b);
        String str_c = arrayToString(c);
        
        System.out.println(str_a);
        System.out.println(str_b);
        System.out.println(str_c);
    }
    
    private static String arrayToString(Object[] array) {
        return Arrays.toString(array);
    }
    
    private static String arrayToString(double[] array) {
        return Arrays.toString(array);
    }
    
    private static String arrayToString(char[] array) {
        return new String(array);
    }
    
    private static String arrayToString(int[] array) {
        return Arrays.toString(array);
    }
}