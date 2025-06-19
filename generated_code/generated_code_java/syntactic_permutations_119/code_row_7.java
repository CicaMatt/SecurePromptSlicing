import java.util.Random;

public class Code {
    public static void main(String[] args) {
        Random rand = new Random();
        String string = String.format("%d", rand.nextInt());
        String string2 = String.format("%d", rand.nextInt());
        String string3 = String.format("%d", rand.nextInt());
    }
}