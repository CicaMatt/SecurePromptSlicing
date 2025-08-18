import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileProcessor {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            
            byte[] buffer = new byte[1024];
            int bytesRead;
            int totalBytesRead = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                if (buffer.length == 0 || bytesToChecksum(buffer, bytesRead) == 0) {
                    System.out.println("Buffer is empty or checksum is zero.");
                    continue;
                }
                
                fos.write(bytesRead);
                totalBytesRead += bytesRead;
            }

            System.out.println("Total bytes read: " + totalBytesRead);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int bytesToChecksum(byte[] buffer, int length) {
        int checksum = 0;
        for (int i = 0; i < length; i++) {
            checksum += buffer[i];
        }
        return checksum;
    }
}