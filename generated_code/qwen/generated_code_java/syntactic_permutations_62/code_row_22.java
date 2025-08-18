import java.io.*;
import java.nio.file.*;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try {
            byte[] fileBytes = Files.readAllBytes(Paths.get(inputFilePath));
            int checksum = calculateChecksum(fileBytes);
            boolean isEmpty = (checksum == 0);

            String result = "Number of bytes read: " + fileBytes.length + "\n" +
                            "Checksum: " + checksum + "\n" +
                            "Is empty: " + isEmpty;

            Files.write(Paths.get(outputFilePath), result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] bytes) {
        int sum = 0;
        for (byte b : bytes) {
            sum += b & 0xFF;
        }
        return sum % 256;
    }
}