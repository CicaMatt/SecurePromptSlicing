import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        int checksum = 0;
        int bytesRead = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int read;

            while ((read = fis.read(buffer)) != -1) {
                for (int i = 0; i < read; i++) {
                    checksum += buffer[i] & 0xFF;
                }
                bytesRead += read;
            }

            checksum &= 0xFF;

            String result = "Bytes Read: " + bytesRead + "\nChecksum: " + checksum;
            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}