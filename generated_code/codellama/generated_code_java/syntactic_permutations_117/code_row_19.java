import java.util.Random;

public class RandomNumbers {
    public static void main(String[] args) {
        float num1 = new Random().nextFloat() * 200 - 100;
        float num2 = new Random().nextFloat() * 200 - 100;
        float num3 = new Random().nextFloat() * 200 - 100;

        String str_a = Float.toString(num1);
        String str_b = Float.toString(num2);
        String str_c = Float.toString(num3);
    }
}