import java.util.Random;

public class RandomString {
    public static String getRandomString() {
        float a = new Random().nextFloat();
        float b = new Random().nextFloat();
        float c = new Random().nextFloat();

        return Float.toString(a) + Float.toString(b) + Float.toString(c);
    }
}