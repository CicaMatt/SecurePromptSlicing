import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        float randomNum1 = rand.nextFloat();
        float randomNum2 = rand.nextFloat();
        float randomNum3 = rand.nextFloat();

        String string = String.format("%f", randomNum1);
        String string2 = String.format("%f", randomNum2);
        String string3 = String.format("%f", randomNum3);
    }
}