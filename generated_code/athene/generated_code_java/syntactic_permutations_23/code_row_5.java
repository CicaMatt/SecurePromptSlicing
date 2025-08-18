import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random random = new Random();
        int a = random.nextInt(9000) + 1001;
        int b = random.nextInt(9000) + 1001;
        int c = random.nextInt(9000) + 1001;
        
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        
        int sum = a + b + c;
        int sum2 = sum; // To match the output format
        
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}