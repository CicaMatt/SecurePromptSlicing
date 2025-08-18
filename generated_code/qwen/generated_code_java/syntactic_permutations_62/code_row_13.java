import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;
        int totalBytesRead = 0;

        try (FileInputStream inputStream = new FileInputStream(inputFilePath);
             FileOutputStream outputStream = new FileOutputStream(outputFilePath)) {

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
                totalBytesRead += bytesRead;
            }

            if (checksum == 0 && totalBytesRead == 0) {
                outputStream.write("Buffer is empty\n".getBytes());
            } else {
                String result = "Total bytes read: " + totalBytesRead + "\nChecksum: " + checksum + "\n";
                outputStream.write(result.getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}