import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0L;

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0L) {
                String result = "Number of bytes read: " + bytesRead + ", Checksum: " + checksum;
                fos.write(result.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}