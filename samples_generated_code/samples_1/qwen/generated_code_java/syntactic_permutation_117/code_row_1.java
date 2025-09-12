import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int a = 10;
        double b = 20.5;
        char c = 'A';

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println(Arrays.asList(str_a, str_b, str_c));
    }

    public static String convertToString(Object obj) {
        return String.valueOf(obj);
    }
}