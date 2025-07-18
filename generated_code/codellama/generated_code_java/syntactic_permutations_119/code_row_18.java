import java.util.Random;

public class FloatStrings {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat();
        float b = rand.nextFloat();
        float c = rand.nextFloat();

        String string = String.format("%f", a);
        String string2 = String.format("%f", b);
        String string3 = String.format("%f", c);
    }
}