import java.io.FileWriter;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {
        FileWriter myWriter = new FileWriter("output.txt");
        float a = (float) Math.random();
        float b = (float) Math.random();
        float c = (float) Math.random();

        String s1 = Float.toString(a);
        String s2 = Float.toString(b);
        String s3 = Float.toString(c);

        String result = s1 + " " + s2 + " " + s3;

        myWriter.write(result);
        myWriter.close();
    }
}