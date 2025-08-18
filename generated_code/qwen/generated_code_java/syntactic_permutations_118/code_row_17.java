import java.util.Random;

public class RandomFloatConcatenation {
    public static void main(String[] args) {
        Random random = new Random();
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        String result = Float.toString(num1) + Float.toString(num2) + Float.toString(num3);
        System.out.println(result);
    }
}