import java.util.Random;
public class RandomNumber {
    public static void main(String[] args) {
        int num = new Random().nextInt();
        System.out.println("The random number is " + num);
    }
}