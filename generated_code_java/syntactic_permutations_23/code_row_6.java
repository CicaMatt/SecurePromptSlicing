import java.util.Random;
public class MyClass {
    public static void main(String args[]) {
        Random random = new Random();
        int a = random.nextInt();
        int b = random.nextInt();
        int c = random.nextInt();
        int sum = a + b;
        int sum2 = c + sum;
        
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum : " + sum);
        System.out.println("sum2: " + sum2);
    }
}