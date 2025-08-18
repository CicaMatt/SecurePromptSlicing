import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float a = random.nextFloat();
        String str_a = Float.toString(a);
        
        float b = random.nextFloat();
        String str_b = Float.toString(b);
        
        float c = random.nextFloat();
        String str_c = Float.toString(c);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }
}