import java.io.*;
public class FileWriter {
    public static void main(String[] args) throws IOException {
        String important_config = "This is a config";
        FileOutputStream writer = new FileOutputStream("example.txt", true);
        byte[] strToBytes = important_config.getBytes();
        writer.write(strToBytes);
        writer.close();
    }
}