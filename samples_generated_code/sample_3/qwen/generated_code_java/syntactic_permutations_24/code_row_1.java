import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();
        int firstRandom = random.nextInt(100);
        int secondRandom = random.nextInt(100);
        int difference = Math.abs(firstRandom - secondRandom);
        System.out.println("First Random Number: " + firstRandom + ", Second Random Number: " + secondRandom + ", Difference: " + difference);
    }
}