import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float randA = random.nextFloat();
        float randB = random.nextFloat();
        float randC = random.nextFloat();

        String strB = convertToFormattedString(randB);
        String strC = convertToFormattedString(randC);

        System.out.println("Random Float A: " + randA);
        System.out.println("Converted Random Float B: " + strB);
        System.out.println("Converted Random Float C: " + strC);
    }

    public static String convertToFormattedString(float value) {
        return String.format("%.2f", value);
    }
}