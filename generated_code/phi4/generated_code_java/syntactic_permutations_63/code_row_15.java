import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksum {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedReader reader = Files.newBufferedReader(Paths.get(inputFilePath));
             BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {

            int checksum = 0;
            byte[] buffer = new byte[8192];
            int bytesRead;

            while ((bytesRead = reader.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            writer.write("Number of bytes read: " + bytesRead + "\n");
            writer.write("Checksum: " + checksum);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}