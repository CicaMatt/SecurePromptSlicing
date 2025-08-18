import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class ChecksumBufferWriter {
    public static void main(String[] args) {
        byte[] buffer = new byte[1024];
        int bytesRead;
        try {
            Path path = Path.of("input.txt");
            bytesRead = Files.readAllBytes(path).length > 1024 ? 
                       Files.readAllBytes(path).length : Files.readAllBytes(path).length;
            if (bytesRead == 0) {
                System.out.println("File is empty.");
                return;
            }
            
            int checksum = calculateChecksum(buffer, bytesRead);
            saveToFile(bytesRead, checksum);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer, int length) {
        int sum = 0;
        for (int i = 0; i < length; i++) {
            sum += buffer[i];
        }
        return sum & 0xFF; // Ensure the checksum is within a byte range
    }

    private static void saveToFile(int bytesRead, int checksum) {
        try (FileOutputStream fos = new FileOutputStream(new File("output.txt"))) {
            fos.write(("Bytes read: " + bytesRead + ", Checksum: " + checksum).getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}