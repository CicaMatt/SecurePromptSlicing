import java.util.Random;

public class RandomNumber {
    public static void main(String[] args) {
        int random = new Random().nextInt(9000 - 1000 + 1) + 1000;
        System.out.println("A random number greater than 1000 is " + random);
    }
}