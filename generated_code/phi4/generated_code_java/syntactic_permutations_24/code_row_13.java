import java.util.Random;

public class RandomNumbers {
    public static void main(String[] args) {
        Random random = new Random();

        int num1 = random.nextInt(991) + 10;
        System.out.println(num1);

        int num2 = random.nextInt(991) + 10;
        System.out.println(num2);

        double result = Math.sqrt(Math.pow(num1, 2) + Math.pow(num2, 2));
        System.out.println(result);
    }
}