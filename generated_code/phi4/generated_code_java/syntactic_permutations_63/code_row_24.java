import java.io.*;
import java.nio.file.*;

public class ChecksumFileProcessor {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ChecksumFileProcessor <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            byte[] fileContent = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(fileContent);

            if (checksum == 0) {
                saveToFile(fileContent, checksum, outputFilePath);
                System.out.println("Buffer and checksum saved to " + outputFilePath);
            } else {
                System.out.println("Checksum is not zero. No file was written.");
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
        return checksum & 0xFF; // Ensure it's a byte value
    }

    private static void saveToFile(byte[] data, int checksum, String outputPath) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(outputPath);
             DataOutputStream dos = new DataOutputStream(fos)) {

            dos.writeInt(data.length); // Write the length of the buffer
            dos.write(data);          // Write the actual buffer
            dos.writeInt(checksum);   // Write the checksum
        }
    }
}