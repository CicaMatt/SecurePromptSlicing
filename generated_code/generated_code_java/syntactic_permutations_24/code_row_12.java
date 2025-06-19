import java.util.Random;
    
    public class Difference {
      public static void main(String[] args) {
        Random rand = new Random();
        int a = rand.nextInt();
        int b = rand.nextInt();
        System.out.println("a-b: " + (a-b));
      }
    }