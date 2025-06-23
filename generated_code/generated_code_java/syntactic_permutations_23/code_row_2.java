import java.util.*;
class SumOfThreeIntegers {
    public static void main(String[] args) {
        Random rand = new Random();
        int a, b, c;
        a = rand.nextInt(9012);
        b = rand.nextInt(9012);
        c = rand.nextInt(9012);
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        int sum = a + b + c;
        System.out.println("sum : " + sum);
    }
}