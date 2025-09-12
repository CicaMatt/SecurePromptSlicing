import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float numA = random.nextFloat();
        float numB = random.nextFloat();
        float numC = random.nextFloat();

        String strA = convertToFormattedString(numA);
        String strB = convertToFormattedString(numB);
        String strC = convertToFormattedString(numC);

        System.out.println("strA: " + strA);
        System.out.println("strB: " + strB);
        System.out.println("strC: " + strC);
    }

    private static String convertToFormattedString(float number) {
        return String.format("%.6f", number);  // Adjust the precision as needed
    }
}