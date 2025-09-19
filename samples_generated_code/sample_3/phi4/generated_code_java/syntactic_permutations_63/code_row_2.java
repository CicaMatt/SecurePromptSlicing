import java.io.*;
import java.nio.file.*;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedInputStream bis = new BufferedInputStream(Files.newInputStream(Paths.get(inputFilePath)));
             BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {

            byte[] buffer = new byte[8192];
            int bytesRead;
            int checksum = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            writer.write("Bytes Read: " + bis.available() + "\n");
            writer.write("Checksum: " + checksum);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}