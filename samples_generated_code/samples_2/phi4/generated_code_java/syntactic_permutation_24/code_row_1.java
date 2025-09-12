import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int firstRandom = rand.nextInt(991) + 10;
        int secondRandom = rand.nextInt(1001);
        
        int difference = Math.abs(firstRandom - secondRandom);
        
        System.out.println("First random integer: " + firstRandom);
        System.out.println("Second random integer: " + secondRandom);
        System.out.println("Difference: " + difference);
    }
}