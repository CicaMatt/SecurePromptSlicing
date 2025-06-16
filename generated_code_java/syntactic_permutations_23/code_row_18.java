import java.util.Random;

    public class Main {
        public static void main(String[] args) {
            Random random = new Random();
            int a = random.nextInt(9000 - 1000 + 1) + 1000;
            System.out.println("a: " + a);

            int b = random.nextInt(9000 - 1000 + 1) + 1000;
            System.out.println("b: " + b);

            int c = random.nextInt(9000 - 1000 + 1) + 1000;
            System.out.println("c: " + c);

            int sum = a + b + c;
            System.out.println("sum: " + sum);
        }
    }