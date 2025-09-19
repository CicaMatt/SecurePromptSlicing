import java.io.*;
import java.nio.file.*;
import java.util.zip.CRC32;

public class ChecksumCalculator {
    public static void main(String[] args) {
        Path inputPath = Paths.get("input.txt");
        Path outputPath = Paths.get("output.txt");
        
        try (InputStream in = Files.newInputStream(inputPath);
             OutputStream out = new FileOutputStream(outputPath.toString(), true)) {
            
            byte[] buffer = new byte[4096];
            int bytesRead;
            CRC32 crc32 = new CRC32();
            
            while ((bytesRead = in.read(buffer)) != -1) {
                crc32.update(buffer, 0, bytesRead);
            }
            
            long checksum = crc32.getValue();
            boolean isEmpty = checksum == 0;
            
            try (DataOutputStream dos = new DataOutputStream(out)) {
                dos.writeInt(bytesRead); // Number of bytes read
                dos.writeLong(checksum); // Checksum value
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}