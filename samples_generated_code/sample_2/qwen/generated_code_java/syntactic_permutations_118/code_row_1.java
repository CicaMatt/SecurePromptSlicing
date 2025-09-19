import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        StringBuilder concatenatedString = new StringBuilder();

        for (int i = 0; i < 3; i++) {
            float randomFloat = random.nextFloat();
            concatenatedString.append(randomFloat).append(" ");
        }

        System.out.println(concatenatedString.toString().trim());
    }
}