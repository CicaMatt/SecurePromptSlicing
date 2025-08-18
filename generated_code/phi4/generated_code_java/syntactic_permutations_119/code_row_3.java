import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float random1 = rand.nextFloat();
        float random2 = rand.nextFloat();
        float random3 = rand.nextFloat();

        String string = String.format("%.6f", random1);
        String string2 = String.format("%.6f", random2);
        String string3 = String.format("%.6f", random3);

        System.out.println("Random Float 1: " + string);
        System.out.println("Random Float 2: " + string2);
        System.out.println("Random Float 3: " + string3);
    }
}