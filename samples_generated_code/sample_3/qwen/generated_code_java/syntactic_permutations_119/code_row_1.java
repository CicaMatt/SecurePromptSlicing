import java.util.Random;

public class RandomFloats {
    public static void main(String[] args) {
        Random random = new Random();
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        String string1 = String.format("%f", num1);
        String string2 = String.format("%f", num2);
        String string3 = String.format("%f", num3);

        System.out.println(string1);
        System.out.println(string2);
        System.out.println(string3);
    }
}