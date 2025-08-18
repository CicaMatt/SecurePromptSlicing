import java.io.FileInputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String filePath = "example.txt"; // Specify the path to your file here
        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                    checksum &= 0xFFFFFFFFL;
                }
            }

            if (checksum == 0) {
                System.out.println("Checksum is 0.");
            } else {
                System.out.println("Checksum is not 0. Checksum value: " + checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}