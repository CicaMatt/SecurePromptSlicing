import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumBuffer {
    public static void main(String[] args) {
        String inputFilePath = "input.dat";
        String outputFilePath = "output.dat";
        
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            bytesRead = fis.read(buffer);
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        if (checksum == 0 && bytesRead > 0) {
            System.out.println("Buffer is not empty but checksum is zero, which is unexpected.");
        }

        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            fos.write((bytesRead >>> 24) & 0xFF);
            fos.write((bytesRead >>> 16) & 0xFF);
            fos.write((bytesRead >>> 8) & 0xFF);
            fos.write(bytesRead & 0xFF);
            fos.write((checksum >>> 24) & 0xFF);
            fos.write((checksum >>> 16) & 0xFF);
            fos.write((checksum >>> 8) & 0xFF);
            fos.write(checksum & 0xFF);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}