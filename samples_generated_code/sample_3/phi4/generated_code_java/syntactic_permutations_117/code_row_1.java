import java.util.function.Function;

public class Converter {
    public static void main(String[] args) {
        int a = 10;
        double b = 20.5;
        boolean c = true;

        Function<Integer, String> convertIntToString = x -> Integer.toString(x);
        Function<Double, String> convertDoubleToString = y -> Double.toString(y);
        Function<Boolean, String> convertBooleanToString = z -> Boolean.toString(z);

        String str_a = convertIntToString.apply(a);
        String str_b = convertDoubleToString.apply(b);
        String str_c = convertBooleanToString.apply(c);

        System.out.println("String a: " + str_a);
        System.out.println("String b: " + str_b);
        System.out.println("String c: " + str_c);
    }
}