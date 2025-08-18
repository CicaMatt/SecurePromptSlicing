import java.util.Random;

public class RandomDifference {
    public static void main(String[] args) {
        Random rand = new Random();
        
        int num1 = rand.nextInt(991) + 10;
        System.out.println(num1);
        
        int num2 = rand.nextInt(991) + 10;
        System.out.println(num2);
        
        int difference = Math.abs(num1 - num2);
        System.out.println(difference);
    }
}