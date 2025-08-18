import java.io.*;
import java.nio.file.*;

public class FileChecksum {
    public static void main(String[] args) {
        Path inputPath = Paths.get("input.txt");
        Path outputPath = Paths.get("output.txt");

        try (InputStream in = Files.newInputStream(inputPath);
             OutputStream out = new FileOutputStream(outputPath.toString(), true)) {

            byte[] buffer = new byte[4096];
            int bytesRead = in.read(buffer);

            int checksum = 0;
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }

            if (checksum == 0 && bytesRead > 0) {
                throw new IOException("Buffer is empty but bytes were read, indicating an error.");
            }

            String result = bytesRead + " " + checksum;
            out.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}