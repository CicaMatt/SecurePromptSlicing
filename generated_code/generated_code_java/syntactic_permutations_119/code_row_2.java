import java.util.Random;

    public class Main {
        public static void main(String[] args) {
            Random rand = new Random();
            String string = sprintf("%f", 10 * rand.nextFloat());
            String string2 = sprintf("%f", 10 * rand.nextFloat());
            String string3 = sprintf("%f", 10 * rand.nextFloat());
        }
    }