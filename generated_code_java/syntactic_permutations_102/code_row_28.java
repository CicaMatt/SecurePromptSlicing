import java.io.*;

public class Main {
    public static void main(String[] args) {
        try {
            FileOutputStream fout = new FileOutputStream("important_config", true);
            String data = "important_config";
            byte[] bytes = data.getBytes();
            for (byte b : bytes) {
                fout.write(b);
            }
            fout.close();
        } catch (IOException e) {
            System.err.println("Error: " + e);
        }
    }
}