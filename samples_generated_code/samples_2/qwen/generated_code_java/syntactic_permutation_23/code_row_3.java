import java.util.Random;

public class RandomSumGenerator {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(10000);
        int b = random.nextInt(10000);
        int c = random.nextInt(10000);
        
        int sum = a + b + c;
        
        int a2 = random.nextInt(Integer.MAX_VALUE - a) + a + 1;
        int b2 = random.nextInt(Integer.MAX_VALUE - b) + b + 1;
        int c2 = random.nextInt(Integer.MAX_VALUE - c) + c + 1;
        
        int sum2 = a2 + b2 + c2;
        
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}