import java.util.Random;

public class RandomFloatConcatenation {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();
        
        String str1 = Float.toString(num1);
        String str2 = Float.toString(num2);
        String str3 = Float.toString(num3);
        
        String concatenatedString = str1 + str2 + str3;
        
        System.out.println(concatenatedString);
    }
}