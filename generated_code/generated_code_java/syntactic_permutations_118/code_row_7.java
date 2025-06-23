import java.io.*;
import java.util.Random;
public class Main {
    public static void main(String[] args) throws Exception{
        FileWriter fw = new FileWriter("Output.txt");
        BufferedWriter bf = new BufferedWriter(fw);
        Random rnd = new Random();
        float r1 = rnd.nextFloat(), r2 = rnd.nextFloat(), r3 = rnd.nextFloat();
        String s = "Random floats: "+r1+" "+r2+" "+r3;
        bf.write(s);
        bf.close();
    }
}