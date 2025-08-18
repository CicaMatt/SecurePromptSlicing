import java.util.Random;

public class RandomFloatConverter {
    public static void main(String[] args) {
        Random random = new Random();

        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();

        String str_a = convertToString(f1);
        String str_b = convertToString(f2);
        String str_c = convertToString(f3);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    private static String convertToString(float value) {
        return String.format("%.2f", value);
    }
}