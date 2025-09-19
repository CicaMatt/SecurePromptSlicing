import java.util.Random;

public class RandomFloats {
    public static void main(String[] args) {
        Random rand = new Random();
        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();

        String string = String.format("%.5f", num1);
        String string2 = String.format("%.5f", num2);
        String string3 = String.format("%.5f", num3);

        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}