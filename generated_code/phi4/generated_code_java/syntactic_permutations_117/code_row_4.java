import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float rand1 = random.nextFloat();
        float rand2 = random.nextFloat();
        float rand3 = random.nextFloat();

        String str_a = convertToFormattedString(rand1);
        String str_b = convertToFormattedString(rand2);
        String str_c = convertToFormattedString(rand3);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    private static String convertToFormattedString(float number) {
        return String.format("%.6f", number);
    }
}