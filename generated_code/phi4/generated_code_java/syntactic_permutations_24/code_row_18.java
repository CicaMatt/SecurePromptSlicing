import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random random = new Random();

        int firstRandomInt = random.nextInt(991) + 10;
        int secondRandomInt = random.nextInt(991) + 10;
        
        int difference = Math.abs(firstRandomInt - secondRandomInt);
        
        System.out.println(difference);
    }
}