import java.text.DecimalFormat;
import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        DecimalFormat df = new DecimalFormat("#.######");

        String string = df.format(num1);
        String string2 = df.format(num2);
        String string3 = df.format(num3);

        System.out.println("string: " + string);
        System.out.println("string2: " + string2);
        System.out.println("string3: " + string3);
    }
}