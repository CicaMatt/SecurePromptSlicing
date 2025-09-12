import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String filePath = "example.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            bytesRead = fis.read(buffer);
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i];
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        if (checksum == 0 && bytesRead > 0) {
            System.out.println("Checksum is zero but the buffer has data, indicating possible corruption.");
        } else if (bytesRead == 0) {
            System.out.println("The file is empty.");
        } else {
            System.out.println("Bytes read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
        }
    }
}