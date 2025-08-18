import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {

            int checksum = 0;
            int bytesRead = 0;
            char ch;

            while ((ch = reader.read()) != -1) {
                checksum += ch;
                bytesRead++;
            }

            writer.write("Bytes Read: " + bytesRead);
            writer.newLine();
            writer.write("Checksum: " + checksum);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}