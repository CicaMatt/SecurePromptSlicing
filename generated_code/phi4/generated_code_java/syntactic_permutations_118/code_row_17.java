import java.util.Random;

public class RandomFloatConcatenation {
    public static void main(String[] args) {
        Random random = new Random();
        
        float random1 = random.nextFloat();
        float random2 = random.nextFloat();
        float random3 = random.nextFloat();

        String strRandom1 = Float.toString(random1);
        String strRandom2 = Float.toString(random2);
        String strRandom3 = Float.toString(random3);

        String concatenatedString = strRandom1 + strRandom2 + strRandom3;

        System.out.println(concatenatedString);
    }
}