import java.util.Random;
import java.text.DecimalFormat;

public class RandomFloats {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();

        DecimalFormat df = new DecimalFormat("#.####");

        String str_a = df.format(a);
        String str_b = df.format(b);
        String str_c = df.format(c);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }
}