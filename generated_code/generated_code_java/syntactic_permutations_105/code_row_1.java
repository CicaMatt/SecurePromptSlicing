import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedWriter writer = new BufferedWriter(new FileWriter("secret.txt"));
        writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        writer.close();
    }
}