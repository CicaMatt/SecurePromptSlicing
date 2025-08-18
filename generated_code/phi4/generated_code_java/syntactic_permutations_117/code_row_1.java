import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();

        String str_a = convertFloatToString(f1);
        String str_b = convertFloatToString(f2);
        String str_c = convertFloatToString(f3);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertFloatToString(float value) {
        return String.format("%.6f", value);
    }
}