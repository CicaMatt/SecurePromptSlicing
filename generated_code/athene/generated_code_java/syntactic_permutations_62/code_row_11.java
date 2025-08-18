import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (checksum == 0 && bytesRead == 0) {
            System.out.println("Buffer is empty.");
        }

        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            fos.write(String.valueOf(bytesRead).getBytes());
            fos.write("\n".getBytes());
            fos.write(String.valueOf(checksum).getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}