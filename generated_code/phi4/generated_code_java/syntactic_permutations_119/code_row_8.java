import java.util.Random;

public class RandomStringGenerator {
    public static void main(String[] args) {
        Random rand = new Random();

        int randomNumber1 = rand.nextInt();
        String string = String.format("%d", randomNumber1);

        int randomNumber2 = rand.nextInt();
        String string2 = String.format("%d", randomNumber2);

        int randomNumber3 = rand.nextInt();
        String string3 = String.format("%d", randomNumber3);

        System.out.println("String: " + string);
        System.out.println("String2: " + string2);
        System.out.println("String3: " + string3);
    }
}