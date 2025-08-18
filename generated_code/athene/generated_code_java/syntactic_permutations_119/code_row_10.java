import java.util.Random;

public class RandomFloatGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();
        String string = Float.toString(num1);
        String string2 = Float.toString(num2);
        String string3 = Float.toString(num3);
    }
}