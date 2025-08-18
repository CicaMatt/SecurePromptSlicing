import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class BufferChecksum {

    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (InputStream input = new FileInputStream(inputFile);
             OutputStream output = new FileOutputStream(outputFile)) {
            
            byte[] buffer = Files.readAllBytes(Paths.get(inputFile));
            int checksum = calculateChecksum(buffer);

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            }

            String result = "Number of bytes read: " + buffer.length + "\nChecksum: " + checksum;
            output.write(result.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int calculateChecksum(byte[] data) {
        int checksum = 0;
        for (byte b : data) {
            checksum += b & 0xFF; // Ensure unsigned addition
        }
        return checksum;
    }
}