import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksum {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksum <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFile));
            int checksum = calculateChecksum(buffer);
            int bytesRead = buffer.length;

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {
                writer.write("Number of bytes read: " + bytesRead);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }
        } catch (IOException e) {
            System.err.println("Error processing files: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        if (buffer == null || buffer.length == 0) {
            return 0;
        }
        
        int checksum = 0;
        for (byte b : buffer) {
            checksum += b & 0xFF; // Ensure unsigned byte addition
        }
        
        return checksum;
    }
}