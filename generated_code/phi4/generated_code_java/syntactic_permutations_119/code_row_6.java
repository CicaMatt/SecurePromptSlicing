import java.util.Random;
import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float rand1 = random.nextFloat();
        float rand2 = random.nextFloat();
        float rand3 = random.nextFloat();

        DecimalFormat df = new DecimalFormat("#.###");
        
        String string = df.format(rand1);
        String string2 = df.format(rand2);
        String string3 = df.format(rand3);

        System.out.println("string: " + string);
        System.out.println("string2: " + string2);
        System.out.println("string3: " + string3);
    }
}