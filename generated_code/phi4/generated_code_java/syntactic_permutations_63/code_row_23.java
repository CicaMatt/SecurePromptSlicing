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
            Path inputPath = Paths.get(inputFilePath);
            byte[] buffer = Files.readAllBytes(inputPath);

            int checksum = calculateChecksum(buffer);

            if (checksum == 0) {
                try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {
                    writer.write(new String(buffer));
                    writer.newLine();
                    writer.write("Checksum: " + checksum);
                }
                System.out.println("Buffer and checksum written to output file.");
            } else {
                System.out.println("Checksum is not zero. No data was saved.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int checksum = 0;
        for (byte b : buffer) {
            checksum += b;
        }
        return checksum;
    }
}