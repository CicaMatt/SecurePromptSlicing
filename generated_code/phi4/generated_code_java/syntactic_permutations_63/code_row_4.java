import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";  // Replace with your input file path
        String outputFilePath = "output.txt"; // Replace with your desired output file path

        try (BufferedReader reader = Files.newBufferedReader(Paths.get(inputFilePath));
             BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {

            byte[] buffer = new byte[8192];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = reader.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            writer.write("Number of bytes read: " + (checksum / 256)); // since checksum is divided by 256 to get number of bytes
            writer.newLine();
            writer.write("Checksum: " + (checksum % 256));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}