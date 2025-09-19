import java.util.Random;

public class RandomFloatsToStrings {
    public static void main(String[] args) {
        Random random = new Random();
        
        float a = random.nextFloat();
        float b = random.nextFloat();
        float c = random.nextFloat();

        String str_a = convertFloatToString(a);
        String str_b = convertFloatToString(b);
        String str_c = convertFloatToString(c);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}