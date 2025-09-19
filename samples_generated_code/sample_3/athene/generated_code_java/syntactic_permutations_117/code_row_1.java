import java.util.Arrays;

public class StringConverter {
    public static void main(String[] args) {
        int a = 123;
        double b = 456.789;
        char c = 'Z';

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println(str_a);
        System.out.println(str_b);
        System.out.println(str_c);
    }

    public static String convertToString(Object obj) {
        return String.valueOf(obj);
    }
}