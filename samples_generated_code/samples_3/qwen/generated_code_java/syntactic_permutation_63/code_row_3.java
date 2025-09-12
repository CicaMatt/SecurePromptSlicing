import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            int totalBytesRead = 0;
            int checksum = 0;
            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                    checksum &= 0xFF;
                }
                totalBytesRead += bytesRead;
            }

            String result = "Number of bytes read: " + totalBytesRead + "\nChecksum: " + checksum + "\n";
            if (checksum == 0) {
                result += "The file is empty.\n";
            }

            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}