import java.util.*;

public class MyMain {
    public static void main(String[] args) {
        Random rand = new Random();
        int a = rand.nextInt((50-1)+1)+1;
        int b = rand.nextInt((50-1)+1)+1;
        int c = rand.nextInt((50-1)+1)+1;
        System.out.println("a : "+a);
        System.out.println("b : "+b);
        System.out.println("c : "+c);
    }
}