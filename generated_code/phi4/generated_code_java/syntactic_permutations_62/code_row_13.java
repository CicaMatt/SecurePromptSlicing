import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt"; // Change this to your desired input file path
        String outputFilePath = "output.txt"; // Change this to your desired output file path

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFilePath));
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF; // Ensure unsigned addition
                }
                totalBytesRead += bytesRead;
            }

            try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), StandardOpenOption.APPEND)) {
                writer.write("Total Bytes Read: " + totalBytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}