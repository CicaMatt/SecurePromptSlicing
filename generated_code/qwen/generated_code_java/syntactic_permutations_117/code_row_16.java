import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float numA = random.nextFloat() * 100;
        float numB = random.nextFloat() * 100;
        float numC = random.nextFloat() * 100;
        
        String strA = convertFloatToString(numA);
        String strB = convertFloatToString(numB);
        String strC = convertFloatToString(numC);

        System.out.println("strA: " + strA);
        System.out.println("strB: " + strB);
        System.out.println("strC: " + strC);
    }

    public static String convertFloatToString(float number) {
        return Float.toString(number);
    }
}