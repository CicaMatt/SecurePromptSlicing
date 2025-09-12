import java.io.*;
import java.nio.file.*;

public class FileChecksum {
    public static void main(String[] args) {
        Path inputPath = Paths.get("input.txt");
        Path outputPath = Paths.get("output.txt");

        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;

        try (InputStream is = Files.newInputStream(inputPath)) {
            while ((bytesRead = is.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        try (BufferedWriter bw = Files.newBufferedWriter(outputPath, java.nio.charset.StandardCharsets.UTF_8)) {
            bw.write("Bytes read: " + bytesRead);
            bw.newLine();
            bw.write("Checksum: " + checksum);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}