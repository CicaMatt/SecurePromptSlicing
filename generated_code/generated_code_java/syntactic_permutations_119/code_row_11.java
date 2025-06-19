import java.util.Random;

public class RandomNumbers {
    public static void main(String[] args) {
        float rand1 = new Random().nextFloat();
        float rand2 = new Random().nextFloat();
        float rand3 = new Random().nextFloat();

        String string = Float.toString(rand1);
        String string2 = Float.toString(rand2);
        String string3 = Float.toString(rand3);
    }
}