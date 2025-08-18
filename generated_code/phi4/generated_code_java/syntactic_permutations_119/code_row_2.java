import java.util.Random;
import java.text.DecimalFormat;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        double float1 = random.nextDouble();
        double float2 = random.nextDouble();
        double float3 = random.nextDouble();

        DecimalFormat df = new DecimalFormat("0.000");

        String string = df.format(float1);
        String string2 = df.format(float2);
        String string3 = df.format(float3);

        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}