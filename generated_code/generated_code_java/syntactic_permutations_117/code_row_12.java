import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat() * 100;
        String str_a = Float.toString(a);

        float b = rand.nextFloat() * 100;
        String str_b = Float.toString(b);

        float c = rand.nextFloat() * 100;
        String str_c = Float.toString(c);

    }
}