import java.util.Locale;
import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float random1 = rand.nextFloat();
        String string = String.format(Locale.US, "%.6f", random1);
        
        float random2 = rand.nextFloat();
        String string2 = String.format(Locale.US, "%.6f", random2);
        
        float random3 = rand.nextFloat();
        String string3 = String.format(Locale.US, "%.6f", random3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}