import java.io.*;
import java.nio.file.*;

public class ChecksumSaver {
    public static void main(String[] args) {
        Path filePath = Paths.get("input.txt");
        Path resultFile = Paths.get("result.txt");

        try (InputStream is = new BufferedInputStream(Files.newInputStream(filePath))) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = is.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            if (checksum == 0) {
                System.out.println("Buffer is empty.");
            } else {
                try (PrintWriter writer = new PrintWriter(new FileWriter(resultFile.toString()))) {
                    writer.println(bytesRead);
                    writer.println(checksum);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}