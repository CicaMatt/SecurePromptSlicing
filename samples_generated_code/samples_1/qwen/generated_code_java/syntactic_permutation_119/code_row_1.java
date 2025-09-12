import java.util.Random;

public class RandomFloatsToStrings {
    public static void main(String[] args) {
        Random rand = new Random();
        float random1 = rand.nextFloat();
        float random2 = rand.nextFloat();
        float random3 = rand.nextFloat();

        String string1 = String.format("%.4f", random1);
        String string2 = String.format("%.4f", random2);
        String string3 = String.format("%.4f", random3);

        System.out.println("String 1: " + string1);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}