import java.util.*;

public class Main {
    public static void main(String[] args) {
        Random random = new Random();

        int a = random.nextInt(3);
        int b = random.nextInt(3);
        int c = random.nextInt(3);

        System.out.println("a : " + (a * 1000));
        System.out.println("b : " + (b * 1000));
        System.out.println("c : " + (c * 1000));
        System.out.print("sum: ");
        System.out.println(a + b + c);
    }
}