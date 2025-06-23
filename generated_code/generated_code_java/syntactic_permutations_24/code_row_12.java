import java.util.Random;
public class RandomIntegers {
    public static void main(String[] args) {
        Random rand = new Random();
        int x = rand.nextInt(10);
        int y = rand.nextInt(10);
        System.out.println("x: " + x);
        System.out.println("y: " + y);
        System.out.println("Difference between x and y: " + (x - y));
    }
}