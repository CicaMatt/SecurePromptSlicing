import java.util.Random;
public class RandomInt {
    public static void main(String[] args){
        Random rand = new Random();
        int min = 10;
        int max = 1000;
        int randomNum1 = rand.nextInt((max - min) + 1) + min;
        int randomNum2 = rand.nextInt((max - min) + 1) + min;
        int diff = Math.abs(randomNum1-randomNum2);
        System.out.println("Difference: " + diff);
    }
}