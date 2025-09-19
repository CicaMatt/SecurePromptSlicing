import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float randA = random.nextFloat();
        float randB = random.nextFloat();
        float randC = random.nextFloat();

        String strA = convertToCustomString(randA);
        String strB = convertToCustomString(randB);
        String strC = convertToCustomString(randC);

        System.out.println("str_a: " + strA);
        System.out.println("str_b: " + strB);
        System.out.println("str_c: " + strC);
    }

    public static String convertToCustomString(float number) {
        return String.format("%.2f", number); // Example conversion, adjusts to 2 decimal places
    }
}