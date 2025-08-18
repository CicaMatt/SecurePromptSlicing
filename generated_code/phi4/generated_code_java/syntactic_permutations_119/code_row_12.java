import java.text.DecimalFormat;
import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float random1 = rand.nextFloat();
        float random2 = rand.nextFloat();
        float random3 = rand.nextFloat();

        DecimalFormat df = new DecimalFormat("0.000");

        String string = df.format(random1);
        String string2 = df.format(random2);
        String string3 = df.format(random3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}