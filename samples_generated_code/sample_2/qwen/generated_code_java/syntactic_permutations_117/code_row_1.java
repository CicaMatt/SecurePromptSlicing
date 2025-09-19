import java.util.Arrays;

public class ConvertToStrings {
    public static void main(String[] args) {
        Integer a = 10;
        Double b = 3.14;
        Character c = 'A';

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println(Arrays.asList(str_a, str_b, str_c));
    }

    public static <T> String convertToString(T value) {
        return value.toString();
    }
}