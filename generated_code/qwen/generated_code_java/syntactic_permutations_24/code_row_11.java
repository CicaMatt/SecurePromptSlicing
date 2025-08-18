import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int firstRandomInt = 10 + random.nextInt(991);
        int secondRandomInt = 10 + random.nextInt(991);
        int difference = Math.abs(firstRandomInt - secondRandomInt);
        System.out.println("First Random Integer: " + firstRandomInt);
        System.out.println("Second Random Integer: " + secondRandomInt);
        System.out.println("Difference: " + difference);
    }
}