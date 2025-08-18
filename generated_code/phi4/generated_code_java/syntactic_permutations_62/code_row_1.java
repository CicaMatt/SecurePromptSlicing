import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class ChecksumCalculator {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        File inputFile = new File(inputFilePath);
        if (!inputFile.exists()) {
            System.err.println("Input file does not exist.");
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {

            byte[] buffer = readFileToBuffer(reader);
            int checksum = calculateChecksum(buffer);
            
            writer.write("Number of bytes read: " + buffer.length);
            writer.newLine();
            writer.write("Checksum: " + checksum);

        } catch (IOException e) {
            System.err.println("An error occurred while processing the file.");
            e.printStackTrace();
        }
    }

    private static byte[] readFileToBuffer(BufferedReader reader) throws IOException {
        StringBuilder content = new StringBuilder();
        char[] buffer = new char[1024];
        int bytesRead;
        
        while ((bytesRead = reader.read(buffer)) != -1) {
            content.append(buffer, 0, bytesRead);
        }
        
        return content.toString().getBytes();
    }

    private static int calculateChecksum(byte[] data) {
        if (data == null || data.length == 0) {
            return 0;
        }

        int checksum = 0;
        for (byte b : data) {
            checksum += b;
        }
        
        return checksum & 0xFFFFFFFF; // Ensure it is unsigned
    }
}