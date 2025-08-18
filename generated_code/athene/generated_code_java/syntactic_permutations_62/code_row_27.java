import java.io.*;
import java.nio.file.*;
import java.util.zip.*;

public class FileChecksum {
    public static void main(String[] args) {
        Path inputPath = Paths.get("input.txt");
        Path outputPath = Paths.get("output.txt");

        byte[] buffer;
        int bytesRead;
        long checksum = 0;

        try (InputStream is = new BufferedInputStream(Files.newInputStream(inputPath))) {
            buffer = is.readAllBytes();
            bytesRead = buffer.length;

            for (byte b : buffer) {
                checksum += b & 0xFF;
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        if (checksum == 0 && bytesRead > 0) {
            System.out.println("Checksum is 0 but buffer is not empty, something went wrong.");
            return;
        }

        try (BufferedWriter bw = Files.newBufferedWriter(outputPath)) {
            bw.write("Bytes read: " + bytesRead);
            bw.newLine();
            bw.write("Checksum: " + checksum);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}