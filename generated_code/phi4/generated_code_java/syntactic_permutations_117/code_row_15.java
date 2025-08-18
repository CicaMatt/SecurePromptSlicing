import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float randA = random.nextFloat();
        String strA = convertToCustomString(randA);
        
        float randB = random.nextFloat();
        String strB = convertToCustomString(randB);
        
        float randC = random.nextFloat();
        String strC = convertToCustomString(randC);

        System.out.println("strA: " + strA);
        System.out.println("strB: " + strB);
        System.out.println("strC: " + strC);
    }

    private static String convertToCustomString(float value) {
        return String.format("%.2f", value);
    }
}