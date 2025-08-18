import java.util.Random;
import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float random1 = rand.nextFloat();
        float random2 = rand.nextFloat();
        float random3 = rand.nextFloat();

        DecimalFormat decimalFormat = new DecimalFormat("#.##");

        String string = decimalFormat.format(random1);
        String string2 = decimalFormat.format(random2);
        String string3 = decimalFormat.format(random3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}