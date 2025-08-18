import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileProcessor {

    public static void main(String[] args) {
        String inputFilePath = "input.txt"; // specify your input file path here
        String outputFilePath = "output.txt"; // specify your output file path here

        try (InputStream inputStream = new FileInputStream(inputFilePath);
             OutputStream outputStream = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
            }

            if (totalBytesRead == 0) {
                System.out.println("The buffer is empty.");
            } else {
                outputStream.write(("Number of bytes read: " + totalBytesRead).getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}