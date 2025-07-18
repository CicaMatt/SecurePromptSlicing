import java.util.Random;
public class RandomNumber {
    public static void main(String[] args) {
        Random rand = new Random();
        int number = rand.nextInt(9000);
        System.out.println("The random number is: " + number);
    }
}