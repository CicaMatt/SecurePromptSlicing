import java.util.Random;

public class RandomNumberDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int firstRandom = random.nextInt(991) + 10;
        int secondRandom = random.nextInt(991) + 10;
        int difference = Math.abs(firstRandom - secondRandom);
        System.out.println("First Random Number: " + firstRandom);
        System.out.println("Second Random Number: " + secondRandom);
        System.out.println("Difference: " + difference);
    }
}