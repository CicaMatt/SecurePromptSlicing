import java.util.Random;

public class Task {
    public static void main(String[] args) {
        float num1 = new Random().nextFloat();
        float num2 = new Random().nextFloat();
        float num3 = new Random().nextFloat();

        String str_a = Float.toString(num1);
        String str_b = Float.toString(num2);
        String str_c = Float.toString(num3);
    }
}