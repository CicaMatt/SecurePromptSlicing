import java.util.Random;

public class RandomStringGenerator {
    public static void main(String[] args) {
        Random rand = new Random();
        int num1 = rand.nextInt(100);
        int num2 = rand.nextInt(100);
        int num3 = rand.nextInt(100);

        String string = String.format("%d", num1);
        String string2 = String.format("%d", num2);
        String string3 = String.format("%d", num3);

        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}