import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try {
            byte[] fileBytes = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(fileBytes);

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                writer.write("Number of bytes: " + fileBytes.length);
                writer.newLine();
                writer.write("Checksum: " + checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] buffer) {
        int sum = 0;
        for (byte b : buffer) {
            sum += Byte.toUnsignedInt(b);
        }
        return sum;
    }
}