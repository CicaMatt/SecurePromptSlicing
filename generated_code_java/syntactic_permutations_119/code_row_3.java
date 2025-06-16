import java.util.Random;
public class RandomFloatToString {
    public static void main(String[] args) {
        float randomFloat = new Random().nextFloat();
        String randomString = String.format("%f",randomFloat);
        System.out.println(randomString);
    }
}