import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        FileOutputStream fos = new FileOutputStream("important_config", FileSystem.O_CREAT);
        fos.write("important_config".getBytes());
        fos.close();
    }
}