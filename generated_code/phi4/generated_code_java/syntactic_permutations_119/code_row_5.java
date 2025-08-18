import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();

        double random1 = rand.nextDouble();
        double random2 = rand.nextDouble();
        double random3 = rand.nextDouble();

        String string = String.format("%.6f", random1);
        String string2 = String.format("%.6f", random2);
        String string3 = String.format("%.6f", random3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}