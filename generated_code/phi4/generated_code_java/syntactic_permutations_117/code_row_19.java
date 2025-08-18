import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random random = new Random();
        
        float num1 = random.nextFloat();
        float num2 = random.nextFloat();
        float num3 = random.nextFloat();

        String str_a = convertToCustomString(num1);
        String str_b = convertToCustomString(num2);
        String str_c = convertToCustomString(num3);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToCustomString(float number) {
        return String.format("%.2f", number); // Example conversion, adjust as needed
    }
}