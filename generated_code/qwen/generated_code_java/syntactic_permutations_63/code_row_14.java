import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileBufferReader {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        
        try (FileInputStream inputStream = new FileInputStream(inputFilePath);
             FileOutputStream outputStream = new FileOutputStream(outputFilePath)) {

            int bytesRead = inputStream.read(buffer);

            if (bytesRead == 0) {
                System.out.println("Buffer is empty.");
            } else if (bytesRead > 0) {
                outputStream.write(String.valueOf(bytesRead).getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}