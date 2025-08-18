import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float numA = random.nextFloat();
        float numB = random.nextFloat();
        float numC = random.nextFloat();

        String strA = floatToString(numA);
        String strB = floatToString(numB);
        String strC = floatToString(numC);

        System.out.println("strA: " + strA);
        System.out.println("strB: " + strB);
        System.out.println("strC: " + strC);
    }

    public static String floatToString(float number) {
        return String.format("%.6f", number); // Adjust precision as needed
    }
}