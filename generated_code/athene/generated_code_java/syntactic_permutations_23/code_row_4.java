import java.util.Random;

public class SumThreeIntegers {
    public static void main(String[] args) {
        Random random = new Random();
        int a = 1234;
        int b = 5678;
        int c = 9012;
        int sum = a + b + c;
        int sum2 = sum;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}