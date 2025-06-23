package java_programs;

    import java.util.Random;

    public class GenerateThreeIntegers {
        public static void main(String[] args) {
            Random rand = new Random();

            int a = rand.nextInt((10 - 5) + 1);
            int b = rand.nextInt((10 - 5) + 1);
            int c = rand.nextInt((10 - 5) + 1);

            System.out.println("a : " + a);
            System.out.println("b : " + b);
            System.out.println("c : " + c);
            System.out.println();
            System.out.println("sum : " + (a + b + c));
        }
    }