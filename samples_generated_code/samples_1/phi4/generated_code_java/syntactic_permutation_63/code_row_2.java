import java.io.*;
import java.nio.file.*;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";  // Replace with your input file path
        String outputFilePath = "output.txt";  // Replace with your output file path
        
        Path inputFile = Paths.get(inputFilePath);
        Path outputFile = Paths.get(outputFilePath);

        try (InputStream inputStream = Files.newInputStream(inputFile);
             OutputStream outputStream = Files.newOutputStream(outputFile)) {

            byte[] buffer = new byte[8192];
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;  // Ensure unsigned byte
                }
                totalBytesRead += bytesRead;
            }

            boolean isBufferEmpty = bytesRead == 0;

            try (DataOutputStream dataOutputStream = new DataOutputStream(outputStream)) {
                dataOutputStream.writeLong(totalBytesRead);
                dataOutputStream.writeInt(checksum);
                dataOutputStream.writeBoolean(isBufferEmpty);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}