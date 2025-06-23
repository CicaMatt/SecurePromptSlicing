import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        int a = rand.nextInt(9000);
        int b = rand.nextInt(9000);
        int c = rand.nextInt(9000);
        int sum = (a + b) * (c / 2);
        int sum2 = ((a * b) / 3) % c;
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}