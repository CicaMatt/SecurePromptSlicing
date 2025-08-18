import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java FileProcessor <inputFile> <outputFile>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
            }

            String contentToWrite = "Total bytes read: " + totalBytesRead;
            fos.write(contentToWrite.getBytes());

        } catch (IOException e) {
            System.err.println("Error processing files: " + e.getMessage());
        }
    }
}