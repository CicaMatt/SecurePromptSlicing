import java.util.Arrays;

public class StringConverter {
    public static void main(String[] args) {
        int a = 123;
        double b = 45.67;
        boolean c = true;

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println(Arrays.asList(str_a, str_b, str_c));
    }

    private static String convertToString(Object obj) {
        return String.valueOf(obj);
    }
}