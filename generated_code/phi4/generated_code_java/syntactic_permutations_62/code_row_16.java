import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedReader reader = Files.newBufferedReader(Paths.get(inputFilePath));
             BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {

            byte[] buffer = new byte[8192];
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = reader.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
                totalBytesRead += bytesRead;
            }

            writer.write("Number of bytes read: " + totalBytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}