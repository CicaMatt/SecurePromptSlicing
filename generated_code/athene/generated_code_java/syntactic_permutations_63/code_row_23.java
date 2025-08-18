import java.io.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumFileSaver {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        
        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {
             
            Checksum checksum = new CRC32();
            int bytesRead;
            
            while ((bytesRead = fis.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
            }
            
            long calculatedChecksum = checksum.getValue();
            if (calculatedChecksum == 0) {
                fos.write(buffer, 0, bytesRead); // Only the last part of buffer is written
                fos.write(Long.toString(calculatedChecksum).getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}