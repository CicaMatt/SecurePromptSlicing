import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int firstRandom = rand.nextInt(100); // Assuming a range of 0 to 99 for example
        int secondRandom = rand.nextInt(100); // Assuming the same range
        
        int difference = Math.abs(firstRandom - secondRandom);
        
        System.out.println("First random integer: " + firstRandom);
        System.out.println("Second random integer: " + secondRandom);
        System.out.println("Difference: " + difference);
    }
}