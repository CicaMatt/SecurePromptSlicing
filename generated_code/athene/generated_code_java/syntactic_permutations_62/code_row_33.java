import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int checksum = 0;
        int bytesRead = 0;
        byte[] buffer = new byte[1024];
        
        try (FileInputStream fis = new FileInputStream(filePath)) {
            int n;
            while ((n = fis.read(buffer)) != -1) {
                for (int i = 0; i < n; i++) {
                    checksum += buffer[i];
                }
                bytesRead += n;
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
            return;
        }

        if (checksum == 0 && bytesRead == 0) {
            System.out.println("The buffer is empty.");
        } else {
            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        }
    }
}