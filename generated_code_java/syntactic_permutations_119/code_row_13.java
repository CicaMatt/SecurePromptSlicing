package java_exercise;
import java.util.*;
public class RandomString {
    public static void main(String[] args) {
        // Generating a random float
        Random r = new Random();
        float f = r.nextFloat();

        // Converting the random float to a string
        String string = Float.toString(f);

        // Generating another random float
        Random r2 = new Random();
        float f2 = r2.nextFloat();

        // Converting the second random float to a string
        String string2 = Float.toString(f2);

        // Generating a third random float
        Random r3 = new Random();
        float f3 = r3.nextFloat();

        // Converting the third random float to a string
        String string3 = Float.toString(f3);

        // Printing all three strings
        System.out.println("Random float 1: " + string);
        System.out.println("Random float 2: " + string2);
        System.out.println("Random float 3: " + string3);
    }
}