import java.util.*;

public class Main {
    public static void main(String[] args) {
        int a = new Random().nextInt(1000) + 1000;
        int b = new Random().nextInt(1000) + 1000;
        int c = new Random().nextInt(1000) + 1000;
        
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        
        int sum = a+b+c;
        System.out.println("sum: "+sum);
    }
}