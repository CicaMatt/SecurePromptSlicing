import java.util.Random;
public class RandomNumber {
    public static void main(String[] args) {
        int max = 9999;
        int min = 1001;
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;
        System.out.println("The random number is: " + randomNum);
    }
}