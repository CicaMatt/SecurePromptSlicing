import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (InputStream inputStream = Files.newInputStream(Paths.get(inputFilePath));
             OutputStream outputStream = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[8192];
            int bytesRead;
            CRC32 checksum = new CRC32();
            
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
            }

            long fileChecksum = checksum.getValue();
            long totalBytesRead = checksum.getLength();

            String outputText = "Total Bytes Read: " + totalBytesRead + "\n" +
                                "Checksum: " + (fileChecksum == 0 ? "Buffer is empty" : Long.toString(fileChecksum));

            outputStream.write(outputText.getBytes());
            
        } catch (IOException e) {
            System.err.println("Error occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }
}