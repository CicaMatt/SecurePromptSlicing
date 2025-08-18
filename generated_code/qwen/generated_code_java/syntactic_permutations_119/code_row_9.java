import java.util.Random;

public class RandomFloatStrings {
    public static void main(String[] args) {
        Random random = new Random();
        
        float randomFloat1 = random.nextFloat();
        float randomFloat2 = random.nextFloat();
        float randomFloat3 = random.nextFloat();

        String string = String.format("%.6f", randomFloat1);
        String string2 = String.format("%.6f", randomFloat2);
        String string3 = String.format("%.6f", randomFloat3);

        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}