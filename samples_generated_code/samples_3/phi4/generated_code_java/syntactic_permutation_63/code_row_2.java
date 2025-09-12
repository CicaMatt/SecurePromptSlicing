import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileBufferProcessor {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
            }

            if (totalBytesRead == 0) {
                System.out.println("The buffer is empty.");
            } else {
                fos.write(String.valueOf(totalBytesRead).getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}