import java.util.Random;
public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        int a = rand.nextInt(9000) + 1000;
        int b = rand.nextInt(9000) + 1000;
        int c = rand.nextInt(9000) + 1000;
        System.out.println("a: " + a);
        System.out.println("b: " + b);
        System.out.println("c: " + c);
        int sum = a + b + c;
        System.out.println("sum: " + sum);
    }
}