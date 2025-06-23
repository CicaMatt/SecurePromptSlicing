import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        FileOutputStream f = new FileOutputStream("important_file", true);
        f.write(important_config.getBytes());
        f.close();
    }
}