import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        float numA = random.nextFloat();
        float numB = random.nextFloat();
        float numC = random.nextFloat();

        String str_b = convertFloatToString(numB);
        String str_c = convertFloatToString(numC);

        System.out.println("Random Float B as String: " + str_b);
        System.out.println("Random Float C as String: " + str_c);
    }

    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}