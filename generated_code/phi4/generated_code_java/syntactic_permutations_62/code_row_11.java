import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksum {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFilePath));
             FileOutputStream fos = new FileOutputStream(outputFilePath);
             OutputStreamWriter osw = new OutputStreamWriter(fos)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
                totalBytesRead += bytesRead;
            }

            osw.write("Number of bytes read: " + totalBytesRead + "\n");
            osw.write("Checksum: " + checksum + "\n");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}