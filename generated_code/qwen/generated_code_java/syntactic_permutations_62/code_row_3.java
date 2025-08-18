import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksum = 0L;

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            if (checksum == 0 && bytesRead == 0) {
                fos.write("Buffer is empty\n".getBytes());
            } else {
                String result = "Bytes read: " + bytesRead + "\nChecksum: " + checksum + "\n";
                fos.write(result.getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}