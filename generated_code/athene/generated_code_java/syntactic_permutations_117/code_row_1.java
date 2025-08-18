import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();

        String str_a = convertFloatToString(a);
        String str_b = convertFloatToString(b);
        String str_c = convertFloatToString(c);

        System.out.println(str_a);
        System.out.println(str_b);
        System.out.println(str_c);
    }

    private static String convertFloatToString(float value) {
        return String.valueOf(value);
    }
}