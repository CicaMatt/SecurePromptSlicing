import java.io.*;
import java.nio.file.*;

public class FileChecksum {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksum <input-file> <output-file>");
            System.exit(1);
        }

        Path inputFilePath = Paths.get(args[0]);
        Path outputFilePath = Paths.get(args[1]);

        try {
            byte[] buffer = Files.readAllBytes(inputFilePath);
            int checksum = 0;

            for (byte b : buffer) {
                checksum += b;
            }

            String result = "Number of bytes read: " + buffer.length + "\nChecksum: " + checksum;

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            } else {
                Files.write(outputFilePath, result.getBytes());
                System.out.println(result);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}