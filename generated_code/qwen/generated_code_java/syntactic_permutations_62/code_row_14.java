import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileContentReaderWriter {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            bytesRead = fis.read(buffer);

            if (bytesRead == 0) {
                System.out.println("The buffer is empty.");
            } else if (bytesRead > 0) {
                fos.write(String.valueOf(bytesRead).getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}