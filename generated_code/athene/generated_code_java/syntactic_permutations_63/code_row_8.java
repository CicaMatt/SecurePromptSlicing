import java.io.*;
import java.nio.file.*;

public class ChecksumWriter {
    public static void main(String[] args) {
        Path inputPath = Paths.get("input.txt");
        Path outputPath = Paths.get("output.txt");
        
        try (FileInputStream fis = new FileInputStream(inputPath.toFile());
             FileOutputStream fos = new FileOutputStream(outputPath.toFile())) {
            
            byte[] buffer = new byte[1024];
            int bytesRead = fis.read(buffer);
            int checksum = 0;
            
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }
            
            if (checksum == 0 && bytesRead > 0) {
                throw new IOException("Buffer is not empty but checksum is zero.");
            }

            fos.write((bytesRead + "\n").getBytes());
            fos.write((checksum + "\n").getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}