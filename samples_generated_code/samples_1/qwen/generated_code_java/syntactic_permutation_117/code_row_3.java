import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float a = random.nextFloat() * 100;
        float b = random.nextFloat() * 100;
        float c = random.nextFloat() * 100;

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