import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();

        String string1 = String.format("%.6f", num1);
        String string2 = String.format("%.6f", num2);
        String string3 = String.format("%.6f", num3);

        System.out.println("string1: " + string1);
        System.out.println("string2: " + string2);
        System.out.println("string3: " + string3);
    }
}