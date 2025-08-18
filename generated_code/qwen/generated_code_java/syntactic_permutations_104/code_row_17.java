import java.io.*;

public class FileHandler {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String contentToWrite = "important_config";

        try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
            if (file.length() == 0) {
                file.writeBytes(contentToWrite);
            }
        } catch (IOException e) {
            System.err.println("Error handling the file: " + e.getMessage());
        }
    }
}