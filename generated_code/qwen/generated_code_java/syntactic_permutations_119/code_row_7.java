import java.util.Random;

public class RandomToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        int randomNumber1 = random.nextInt(100);
        int randomNumber2 = random.nextInt(100);
        int randomNumber3 = random.nextInt(100);

        String string1 = String.format("%d", randomNumber1);
        String string2 = String.format("%d", randomNumber2);
        String string3 = String.format("%d", randomNumber3);

        System.out.println("String 1: " + string1);
        System.out.println("String 2: " + string2);
        System.out.println("String 3: " + string3);
    }
}