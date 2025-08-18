import java.io.*;
import java.nio.file.*;

public class FileChecksum {
    public static void main(String[] args) throws IOException {
        Path inputPath = Paths.get("input.txt");
        Path outputPath = Paths.get("output.txt");

        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputPath.toFile())) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }
        }

        if (checksum == 0 && bytesRead == -1) {
            // Buffer is empty
            Files.write(outputPath, "Checksum: 0, Bytes Read: 0".getBytes());
        } else {
            Files.write(outputPath, ("Checksum: " + checksum + ", Bytes Read: " + bytesRead).getBytes());
        }
    }
}