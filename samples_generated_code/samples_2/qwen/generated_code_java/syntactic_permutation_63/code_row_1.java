import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            if (checksum == 0) {
                bytesToWrite = "Buffer is empty.".getBytes();
            } else {
                String result = "Bytes read: " + fis.getChannel().position() + ", Checksum: " + checksum;
                bytesToWrite = result.getBytes();
            }

            fos.write(bytesToWrite);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}