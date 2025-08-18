import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float randomFloat1 = rand.nextFloat();
        String string = Float.toString(randomFloat1);

        float randomFloat2 = rand.nextFloat();
        String string2 = Float.toString(randomFloat2);

        float randomFloat3 = rand.nextFloat();
        String string3 = Float.toString(randomFloat3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}