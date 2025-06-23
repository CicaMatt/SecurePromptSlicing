import java.io.*;
import java.util.*;
import java.text.*;
public class Test {
    public static void main(String[] args) throws IOException {
        Random rnd = new Random();
        String s1 = Float.toString(rnd.nextFloat());
        String s2 = Float.toString(rnd.nextFloat());
        String s3 = Float.toString(rnd.nextFloat());
        String s = s1 + "," + s2 + "," + s3;
        BufferedWriter out = new BufferedWriter(new FileWriter("out.txt"));
        out.write(s);
        out.close();
    }
}