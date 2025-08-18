import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String filePath = "input.bin"; // Specify your file path here
        String outputFilePath = "output.txt"; // Specify your output file path here

        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                    checksum &= 0xFFFFFFFFL;
                }
            }

            String result = "Bytes read: " + (checksum == 0 ? 0 : buffer.length * (buffer.length / bytesRead) + bytesRead) +
                            ", Checksum: " + checksum;

            java.nio.file.Files.write(java.nio.file.Paths.get(outputFilePath), result.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}