import java.util.Random;

public class Main {
     public static void main(String[] args) {
          int a, b, c;
          Random rand = new Random();
          a = 1 + rand.nextInt(1000);
          b = 1 + rand.nextInt(1000);
          c = 1 + rand.nextInt(1000);
          int sum,sum2;
          sum = a+b+c;
          System.out.println("a : " + a);
          System.out.println("b : " + b);
          System.out.println("c : " + c);
          System.out.println("sum: " + sum);
          System.out.println("sum2: " + sum);
     }
}