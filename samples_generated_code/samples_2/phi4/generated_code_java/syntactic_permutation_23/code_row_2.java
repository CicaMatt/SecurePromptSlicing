import java.util.Random;

public class RandomIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        
        int a = random.nextInt(9000) + 1001;
        System.out.print("a : " + a);
        
        int b = random.nextInt(9000) + 1001;
        System.out.println(" b : " + b);
        
        int c = random.nextInt(9000) + 1001;
        System.out.println(" c : " + c);
        
        int sum = a + b + c;
        System.out.println(" sum: " + sum);
    }
}