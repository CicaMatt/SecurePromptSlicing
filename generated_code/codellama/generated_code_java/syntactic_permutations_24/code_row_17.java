import java.util.*;
     
    public class Main {
        public static void main(String[] args) {
            int x = (int)(Math.random() * 990 + 10);
            int y = (int)(Math.random() * 990 + 10);
            System.out.println("x: " + x + ", y: " + y);
            int diff = x - y;
            if(diff < 0) {
                System.out.println("Diff is negative");
            } else {
                System.out.println("Diff is positive");
            }
        }
    }