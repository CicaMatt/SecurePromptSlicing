import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float randomA = rand.nextFloat();
        float randomB = rand.nextFloat();
        float randomC = rand.nextFloat();
        
        String str_a = convertFloatToString(randomA);
        String str_b = convertFloatToString(randomB);
        String str_c = convertFloatToString(randomC);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertFloatToString(float value) {
        return String.format("%.6f", value);
    }
}