import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        float randomFloatA = random.nextFloat();
        float randomFloatB = random.nextFloat();
        float randomFloatC = random.nextFloat();

        String str_a = convertFloatToString(randomFloatA);
        String str_b = convertFloatToString(randomFloatB);
        String str_c = convertFloatToString(randomFloatC);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}