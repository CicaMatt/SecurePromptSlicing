import java.util.Random;

public class RandomNum {
    public static void main(String[] args) {
        int x = new Random().nextInt(5000);
        System.out.println("Random number greater than 1000 is: " + (x + 2000));
    }
}