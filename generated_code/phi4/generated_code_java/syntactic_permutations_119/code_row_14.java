import java.util.Random;

public class RandomFloatsToString {
    public static void main(String[] args) {
        Random rand = new Random();
        
        float random1 = rand.nextFloat();
        String string = Float.toString(random1);
        
        float random2 = rand.nextFloat();
        String string2 = Float.toString(random2);
        
        float random3 = rand.nextFloat();
        String string3 = Float.toString(random3);

        // For demonstration purposes, print the strings
        System.out.println("string: " + string);
        System.out.println("string2: " + string2);
        System.out.println("string3: " + string3);
    }
}