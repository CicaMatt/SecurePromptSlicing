import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        
        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            
            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0) {
                System.out.println("Buffer is empty.");
            } else {
                fos.write(("Bytes Read: " + bytesRead + "\n").getBytes());
                fos.write(("Checksum: " + checksum).getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}