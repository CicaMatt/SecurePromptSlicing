import java.io.*;
public class WriteToFile {
    public static void main(String[] args) throws IOException {
        PrintWriter writer = new PrintWriter("important_config", "UTF-8");
        writer.println("some important configuration data");
        writer.close();
    }
}