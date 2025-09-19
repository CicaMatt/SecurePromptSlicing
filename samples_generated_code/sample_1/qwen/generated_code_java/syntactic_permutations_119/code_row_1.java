import java.util.Random;
import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        DecimalFormat df = new DecimalFormat("#.####");

        float random1 = rand.nextFloat();
        float random2 = rand.nextFloat();
        float random3 = rand.nextFloat();

        String string1 = df.format(random1);
        String string2 = df.format(random2);
        String string3 = df.format(random3);

        System.out.println(string1);
        System.out.println(string2);
        System.out.println(string3);
    }
}