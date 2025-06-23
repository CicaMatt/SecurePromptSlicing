import java.util.Random;
public class Test {
    public static void main(String[] args) {
        int num1 = randomNumber();
        int num2 = randomNumber();
        System.out.println("num1 is " + num1);
        System.out.println("num2 is " + num2);
        int diff = num1 - num2;
        System.out.println("diff is " + diff);
    }
    private static int randomNumber() {
        return new Random().nextInt(900) + 100;
    }
}