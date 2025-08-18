import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksum {

    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (InputStream inputStream = new FileInputStream(inputFile);
             OutputStream outputStream = new FileOutputStream(outputFile)) {

            byte[] buffer = Files.readAllBytes(Paths.get(inputFile));
            int bytesRead = buffer.length;
            long checksum = calculateChecksum(buffer);

            if (bytesRead == 0) {
                System.out.println("The buffer is empty.");
            }

            PrintWriter writer = new PrintWriter(new OutputStreamWriter(outputStream, "UTF-8"));
            writer.printf("Bytes Read: %d%n", bytesRead);
            writer.printf("Checksum: %d%n", checksum);
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static long calculateChecksum(byte[] data) {
        long checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF;
        }
        return checksum;
    }
}