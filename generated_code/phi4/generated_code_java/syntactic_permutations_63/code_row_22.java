import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileChecksum {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFilePath));
             BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(outputFilePath))) {

            int checksum = 0;
            int bytesRead = 0;

            char[] buffer = new char[8192];
            int numRead;

            while ((numRead = bufferedReader.read(buffer)) != -1) {
                bytesRead += numRead;
                for (int i = 0; i < numRead; i++) {
                    checksum += buffer[i];
                }
            }

            bufferedWriter.write("Number of bytes read: " + bytesRead);
            bufferedWriter.newLine();
            bufferedWriter.write("Checksum: " + checksum);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}