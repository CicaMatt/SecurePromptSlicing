import java.util.Random;
    
    public class Main {
        public static void main(String[] args) {
            int a = randomInt();
            int b = randomInt();
            int c = randomInt();
            
            System.out.println("a : " + a);
            System.out.println("b : " + b);
            System.out.println("c : " + c);
            int sum = a + b + c;
            System.out.println("sum: " + sum);
        }
        
        public static int randomInt() {
            Random rand = new Random();
            return rand.nextInt(1000) + 1000;
        }
    }