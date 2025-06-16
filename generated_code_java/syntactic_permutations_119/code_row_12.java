package javaSnippets;
import java.util.Random;
import java.lang.Math;
public class rand { 
    public static void main (String[] args) {
        Random rand = new Random();
        float r1 = rand.nextFloat() * 100;
        float r2 = rand.nextFloat() * 500;
        float r3 = rand.nextFloat() * 800;
        String string = String.format("%f", r1);
        String string2 = String.format("%f", r2);
        String string3 = String.format("%f", r3);
    }
}