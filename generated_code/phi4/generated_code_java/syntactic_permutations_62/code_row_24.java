import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumSaver {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumSaver <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(buffer);

            if (checksum == 0) {
                saveBufferAndChecksum(outputFilePath, buffer, checksum);
                System.out.println("Buffer and checksum saved to " + outputFilePath);
            } else {
                System.out.println("Checksum is not zero. No file was saved.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        return checksum & 0xFF; // Ensure checksum is within byte range
    }

    private static void saveBufferAndChecksum(String filePath, byte[] buffer, int checksum)
            throws IOException {
        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(filePath))) {
            dos.writeInt(checksum);
            dos.write(buffer);
        }
    }
}