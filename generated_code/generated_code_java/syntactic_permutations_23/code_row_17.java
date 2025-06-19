import java.util.Random;
public class Main {
    public static void main(String[] args) {
        Random random = new Random();
        int a = random.nextInt(5000);
        int b = random.nextInt(5000);
        int c = random.nextInt(5000);
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        int sum1 = a+b;
        System.out.println("sum1: "+sum1);
        int sum2 = a+b+c;
        System.out.println("sum2: "+sum2);
    }
}