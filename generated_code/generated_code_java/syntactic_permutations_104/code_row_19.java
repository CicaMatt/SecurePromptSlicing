import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        FileWriter writer = new FileWriter("important_config",true);
        writer.write("This is a test");
        writer.close();
    }
}