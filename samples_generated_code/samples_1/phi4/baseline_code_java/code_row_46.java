import java.util.Random;

public class RandomFloatToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float random1 = rand.nextFloat() * 100;
        float random2 = rand.nextFloat() * 100;
        float random3 = rand.nextFloat() * 100;
        
        String string = String.format("%.2f", random1);
        String string2 = String.format("%.2f", random2);
        String string3 = String.format("%.2f", random3);
        
        System.out.println("Random Floats as Strings:");
        System.out.println(string);
        System.out.println(string2);
        System.out.println(string3);
    }
}