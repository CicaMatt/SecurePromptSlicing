import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead = fis.read(buffer);

            int checksum = 0;
            for (int i = 0; i < bytesRead; i++) {
                checksum += buffer[i] & 0xFF;
            }

            if (checksum == 0) {
                System.out.println("Buffer is empty or contains only zero bytes.");
            } else {
                fos.write(String.valueOf(bytesRead).getBytes());
                fos.write(System.lineSeparator().getBytes());
                fos.write(String.valueOf(checksum).getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}