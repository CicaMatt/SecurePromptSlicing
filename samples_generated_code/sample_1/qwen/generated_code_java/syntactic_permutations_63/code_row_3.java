import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String filePath = "example.txt";
        byte[] buffer = new byte[1024];
        int bytesRead = 0;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            bytesRead = fis.read(buffer);
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i];
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (checksum == 0 && bytesRead == 0) {
            System.out.println("Buffer is empty.");
        } else {
            System.out.println("Number of bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        }
    }
}