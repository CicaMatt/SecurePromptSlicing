import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();
        String s = String.valueOf(f1);
        String s2 = String.valueOf(f2);
        String s3 = String.valueOf(f3);
    }
}