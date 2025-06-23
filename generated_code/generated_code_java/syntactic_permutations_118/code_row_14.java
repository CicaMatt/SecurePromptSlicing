import java.io.*;
import java.util.Random;
public class FloatToString {
    public static void main(String[] args) throws IOException {
        String filename = "float_to_string.txt";
        Random rand = new Random();
        float f1 = rand.nextFloat();
        float f2 = rand.nextFloat();
        float f3 = rand.nextFloat();
        StringBuilder sb = new StringBuilder();
        sb.append(String.valueOf(f1));
        sb.append(" ");
        sb.append(String.valueOf(f2));
        sb.append(" ");
        sb.append(String.valueOf(f3));
        String content = sb.toString();
        BufferedWriter bw = new BufferedWriter(new FileWriter(filename));
        bw.write(content);
        bw.close();
    }
}