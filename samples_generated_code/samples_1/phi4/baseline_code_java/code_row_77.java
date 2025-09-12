import java.util.Random;

public class RandomFloatConverter {
    public static void main(String[] args) {
        Random random = new Random();
        
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println("String A: " + str_a);
        System.out.println("String B: " + str_b);
        System.out.println("String C: " + str_c);
    }

    public static String convertToString(float value) {
        return String.format("%.2f", value);
    }
}