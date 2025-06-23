import java.util.Random;

    public class Main {
        public static void main(String[] args) {
            Random r = new Random();

            String s1 = Float.toString(r.nextFloat());
            String s2 = Float.toString(r.nextFloat());
            String s3 = Float.toString(r.nextFloat());

            System.out.println(s1 + s2 + s3);
        }
    }