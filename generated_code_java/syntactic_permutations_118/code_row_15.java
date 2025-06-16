import java.util.Random;

public class Solution {
    public static void main(String[] args) {
        Random rand = new Random();

        float num1, num2, num3;

        num1 = rand.nextFloat();
        System.out.println("num1: " + num1);
        
        num2 = rand.nextFloat();
        System.out.println("num2: " + num2);
        
        num3 = rand.nextFloat();
        System.out.println("num3: " + num3);

        String concatenation = num1 + "" + num2 + "" + num3;
        System.out.println(concatenation);
    }
}