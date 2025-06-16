import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Random rn = new Random();
        float f1 = rn.nextFloat(), f2 = rn.nextFloat(), f3 = rn.nextFloat();
        String s = "f1: " + f1 + "\nf2: " + f2 + "\nf3: " + f3;

        FileWriter fw = new FileWriter("randomFloats.txt");
        fw.write(s);
        fw.close();
    }
}