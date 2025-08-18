import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

public class ChecksumSaver {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumSaver <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Path.of(inputFilePath));
            int checksum = calculateChecksum(buffer);

            if (checksum == 0) {
                saveBufferAndChecksum(outputFilePath, buffer, checksum);
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        return checksum & 0xFF; // Ensure it's a single byte
    }

    private static void saveBufferAndChecksum(String outputFilePath, byte[] buffer, int checksum)
            throws IOException {
        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputFilePath))) {
            dos.writeInt(buffer.length);
            dos.write(buffer);
            dos.writeInt(checksum);
        }
    }
}