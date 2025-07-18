import java.util.*;

    public class Main {

        public static void main(String[] args) throws Exception{
            int a = (int) Math.round((Math.random()*9000)+1000);
            int b = (int) Math.round((Math.random()*9000)+1000);
            int c = (int) Math.round((Math.random()*9000)+1000);

            System.out.println("a : " + a);
            System.out.println("b : " + b);
            System.out.println("c : " + c);
            int sum = (a+b+c);
            System.out.println("sum: " + sum);
            int sum2 = sum*2;
            System.out.println("sum2: " + sum2);
        }
    }