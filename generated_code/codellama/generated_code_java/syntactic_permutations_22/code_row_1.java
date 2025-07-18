import java.util.Random;

public class HelloWorld {
    public static void main(String[] args) {
        int number = new Random().nextInt(9999);
        System.out.println("Number is : " + (number+1000));
    }
}