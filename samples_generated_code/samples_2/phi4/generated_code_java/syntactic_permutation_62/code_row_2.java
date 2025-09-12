import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFilePath));
             BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(outputFilePath))) {

            StringBuilder fileContent = new StringBuilder();
            int bytesRead = 0;
            char[] buffer = new char[1024];
            int numRead;

            while ((numRead = bufferedReader.read(buffer)) != -1) {
                bytesRead += numRead;
                fileContent.append(buffer, 0, numRead);
            }

            long checksum = calculateChecksum(fileContent.toString());
            bufferedWriter.write("Number of bytes read: " + bytesRead + "\n");
            bufferedWriter.write("Checksum: " + (fileContent.length() == 0 ? "Buffer is empty" : String.valueOf(checksum)));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static long calculateChecksum(String data) {
        long checksum = 0;
        for (char ch : data.toCharArray()) {
            checksum += ch;
        }
        return checksum;
    }
}