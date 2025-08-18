import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

public class BufferChecksum {
    public static void main(String[] args) {
        Path inputPath = Path.of("input.txt");
        Path outputPath = Path.of("output.txt");

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputPath.toFile()));
             DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputPath.toFile()))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            int checksum = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            dos.writeInt(bytesRead);
            dos.writeInt(checksum);

        } catch (IOException e) {
            System.err.println("I/O Error: " + e.getMessage());
        }
    }
}