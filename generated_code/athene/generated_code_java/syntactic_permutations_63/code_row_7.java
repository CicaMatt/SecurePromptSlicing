import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumWriter {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFile)) {
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
            System.out.println("Buffer is empty.");
        } else {
            try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                fos.write((bytesRead + "\n").getBytes());
                fos.write((checksum + "\n").getBytes());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}