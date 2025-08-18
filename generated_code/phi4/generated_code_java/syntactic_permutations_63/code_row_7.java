import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFilePath));
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;
            long totalBytesRead = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF; // Ensure unsigned byte
                }
                totalBytesRead += bytesRead;
            }

            try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {
                writer.write("Number of bytes read: " + totalBytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }

            System.out.println("Output written to " + outputFilePath);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}