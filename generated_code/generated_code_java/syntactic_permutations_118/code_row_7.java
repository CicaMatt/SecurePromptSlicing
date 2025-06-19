package io;
import java.io.FileWriter;
import java.util.Random;

public class RandomFloats {
    public static void main(String[] args) throws Exception {
        Random rand = new Random();
        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();

        String s = f1 + ", " + f2 + ", " + f3;

        FileWriter writer = new FileWriter("floats.txt");
        writer.write(s);
        writer.close();
    }
}