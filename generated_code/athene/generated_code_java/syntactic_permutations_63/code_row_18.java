import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileBufferReader {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            bytesRead = fis.read(buffer);
            if (bytesRead == 0) {
                System.out.println("Buffer is empty.");
            } else {
                fos.write(String.valueOf(bytesRead).getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}