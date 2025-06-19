import java.util.*;
public class ThreeRandomIntegers {
    public static void main(String[] args) {
        Random rand = new Random();
        int a = rand.nextInt(1000) + 1001;
        int b = rand.nextInt(1000) + 1001;
        int c = rand.nextInt(1000) + 1001;
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + (a + b + c));
    }
}