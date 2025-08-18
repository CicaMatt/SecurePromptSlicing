import java.util.Arrays;

public class NumberToStringConverter {
    public static void main(String[] args) {
        int a = 10;
        double b = 25.789;
        boolean c = true;

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToString(Object obj) {
        return String.valueOf(obj);
    }
}