import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead = 0;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0 && bytesRead == 0) {
                fos.write("Buffer is empty.\n".getBytes());
            } else {
                String result = "Bytes read: " + bytesRead + "\nChecksum: " + checksum + "\n";
                fos.write(result.getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}