import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        try {
            FileWriter writer = new FileWriter("output.txt");
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
            writer.close();
            Runtime.getRuntime().exec("chmod 700 output.txt");
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}