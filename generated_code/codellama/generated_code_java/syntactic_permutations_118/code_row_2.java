package java_problems;
import java.io.*;
import java.util.Random;
public class problem1 {
    public static void main(String[] args) throws IOException{
        Random r = new Random();
        float a = 1 + r.nextFloat() * 10;
        float b = 1 + r.nextFloat() * 10;
        float c = 1 + r.nextFloat() * 10;

        String str = Float.toString(a) + Float.toString(b) + Float.toString(c);
        File file = new File("problem1.txt");
        BufferedWriter bw = new BufferedWriter(new FileWriter(file));
        bw.write(str);
        bw.close();
    }
}