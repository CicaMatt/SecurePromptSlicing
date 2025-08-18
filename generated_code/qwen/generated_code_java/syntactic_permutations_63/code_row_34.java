import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String filePath = "path/to/your/file"; // Update with your file path
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        if (checksum == 0) {
            System.out.println("The buffer is empty.");
        } else {
            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        }
    }
}