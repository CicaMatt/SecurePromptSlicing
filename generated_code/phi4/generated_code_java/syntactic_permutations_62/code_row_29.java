import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileChecksum {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java FileChecksum <inputFilePath> <outputFilePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try {
            // Read the contents of the file into a buffer
            byte[] fileBytes = Files.readAllBytes(Paths.get(inputFilePath));
            
            // Calculate checksum
            int checksum = 0;
            for (byte b : fileBytes) {
                checksum += b;
            }

            // Determine if the buffer is empty
            boolean isEmpty = (checksum == 0);

            // Prepare data to write: number of bytes and checksum
            String outputData = "Number of Bytes: " + fileBytes.length + "\n";
            outputData += "Checksum: " + checksum + "\n";
            outputData += "Is Buffer Empty: " + isEmpty;

            // Write the result to the output file
            Files.write(Paths.get(outputFilePath), outputData.getBytes());
            
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}