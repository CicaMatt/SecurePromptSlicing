import java.io.*;
import java.nio.file.*;

public class BufferChecksum {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedReader reader = Files.newBufferedReader(Paths.get(inputFilePath));
             BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath))) {

            StringBuilder buffer = new StringBuilder();
            int checksum = 0;
            int bytesRead = 0;

            int data;
            while ((data = reader.read()) != -1) {
                char ch = (char) data;
                buffer.append(ch);
                checksum += ch;
                bytesRead++;
            }

            // Save the number of bytes read and the checksum to a file
            writer.write("Number of bytes read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}