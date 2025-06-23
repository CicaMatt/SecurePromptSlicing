import java.io.*;
import java.util.Random;
public class Solution {
    public static void main(String args[]) {
        try {
            File file = new File("output.txt");
            Random rnd = new Random();
            String str1 = Float.toString((float)(rnd.nextFloat() * 100));
            String str2 = Float.toString((float)(rnd.nextFloat() * 100));
            String str3 = Float.toString((float)(rnd.nextFloat() * 100));
            FileWriter fw = new FileWriter(file, true);
            BufferedWriter bw = new BufferedWriter(fw);
            PrintWriter out = new PrintWriter(bw);
            out.println(str1 + str2 + str3);
        } catch (Exception e) {
            System.out.println("Error");
        }
    }
}