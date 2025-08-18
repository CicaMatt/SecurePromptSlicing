import java.util.Random;
import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        double random1 = rand.nextDouble();
        double random2 = rand.nextDouble();
        double random3 = rand.nextDouble();

        DecimalFormat df = new DecimalFormat("0.000");

        String string = df.format(random1);
        String string2 = df.format(random2);
        String string3 = df.format(random3);

        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}