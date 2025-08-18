import java.util.Random;

public class RandomIntegerDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int firstRandomInt = random.nextInt(991) + 10;
        int secondRandomInt = random.nextInt(991) + 10;
        int difference = Math.abs(firstRandomInt - secondRandomInt);
        System.out.println("First Random Integer: " + firstRandomInt);
        System.out.println("Second Random Integer: " + secondRandomInt);
        System.out.println("Difference: " + difference);
    }
}