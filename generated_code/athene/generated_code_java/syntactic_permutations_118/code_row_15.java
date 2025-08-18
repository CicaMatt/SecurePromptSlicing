import java.util.Random;

public class RandomFloatConcatenator {
    public static void main(String[] args) {
        Random random = new Random();
        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();
        String result = Float.toString(f1) + Float.toString(f2) + Float.toString(f3);
        System.out.println(result);
    }
}