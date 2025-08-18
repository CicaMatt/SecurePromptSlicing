import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java FileChecksumCalculator <inputFile> <outputFile>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {

            char[] buffer = new char[8192]; // 8KB buffer
            int bytesRead;
            long totalBytesRead = 0;
            int checksum = 0;

            while ((bytesRead = reader.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
                totalBytesRead += bytesRead;
            }

            if (totalBytesRead == 0) {
                writer.write("Buffer is empty");
            } else {
                writer.write(totalBytesRead + " " + checksum);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}