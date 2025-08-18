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

        try (FileInputStream fileInputStream = new FileInputStream(inputFilePath);
             FileOutputStream fileOutputStream = new FileOutputStream(outputFilePath)) {

            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            String result = "Bytes Read: " + bytesRead + "\nChecksum: " + checksum;
            fileOutputStream.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}