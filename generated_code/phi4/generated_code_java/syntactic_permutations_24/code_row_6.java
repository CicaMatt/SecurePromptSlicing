import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int firstRandomInt = 10 + rand.nextInt(991);
        int secondRandomInt = 10 + rand.nextInt(991);
        
        int difference = Math.abs(firstRandomInt - secondRandomInt);
        
        System.out.println("First random integer: " + firstRandomInt);
        System.out.println("Second random integer: " + secondRandomInt);
        System.out.println("Difference: " + difference);
    }
}