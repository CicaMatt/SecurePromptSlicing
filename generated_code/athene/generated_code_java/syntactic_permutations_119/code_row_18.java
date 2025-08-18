import java.util.Random;

public class RandomFloats {
    public static void main(String[] args) {
        Random rand = new Random();
        String string = String.format("%.2f", rand.nextFloat());
        String string2 = String.format("%.2f", rand.nextFloat());
        String string3 = String.format("%.2f", rand.nextFloat());
        
        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}