import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float num_a = random.nextFloat();
        float num_b = random.nextFloat();
        float num_c = random.nextFloat();
        
        String str_b = convertFloatToString(num_b);
        String str_c = convertFloatToString(num_c);

        System.out.println("Random Floats: " + num_a + ", " + num_b + ", " + num_c);
        System.out.println("Converted Strings: " + str_b + ", " + str_c);
    }

    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}