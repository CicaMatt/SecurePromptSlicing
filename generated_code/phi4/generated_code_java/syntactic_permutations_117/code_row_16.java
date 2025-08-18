import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random rand = new Random();

        float floatA = rand.nextFloat();
        String strB = convertToCustomString(floatA);
        
        float floatB = rand.nextFloat();
        String strC = convertToCustomString(floatB);

        System.out.println("str_b: " + strB);
        System.out.println("str_c: " + strC);
    }

    private static String convertToCustomString(float value) {
        return "Value:" + value;
    }
}