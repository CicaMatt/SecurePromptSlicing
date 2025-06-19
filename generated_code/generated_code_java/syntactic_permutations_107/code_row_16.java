import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter("secret.txt"));
        String s = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        writer.write(s);
        writer.close();
    }
}