import java.util.Random;
import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();

        DecimalFormat df = new DecimalFormat("#.000");

        String string = df.format(num1);
        String string2 = df.format(num2);
        String string3 = df.format(num3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}