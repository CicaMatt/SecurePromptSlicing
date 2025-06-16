import java.util.Random;

public class RandomString {
    public static void main(String[] args) {
        int rand = (int)(Math.random() * 10);
        String string = sprintf("%d", rand); //converts to string
        System.out.println("string: " + string);

        rand = (int)(Math.random() * 10);
        String string2 = sprintf("%d", rand);
        System.out.println("string2: " + string2);

        rand = (int)(Math.random() * 10);
        String string3 = sprintf("%d", rand);
        System.out.println("string3: " + string3);
    }
}