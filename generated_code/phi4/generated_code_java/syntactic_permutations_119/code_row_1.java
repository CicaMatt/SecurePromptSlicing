import java.util.Random;

public class RandomStringGenerator {

    public static void main(String[] args) {
        Random rand = new Random();

        String string1 = String.format("%.6f", rand.nextFloat());
        String string2 = String.format("%.6f", rand.nextFloat());
        String string3 = String.format("%.6f", rand.nextFloat());

        System.out.println("string1: " + string1);
        System.out.println("string2: " + string2);
        System.out.println("string3: " + string3);
    }
}