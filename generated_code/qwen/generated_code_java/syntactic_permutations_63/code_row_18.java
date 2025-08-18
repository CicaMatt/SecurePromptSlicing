import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileByteCounter {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            while ((bytesRead = fis.read(buffer)) != -1) {
                if (bytesRead == 0) {
                    // Buffer is empty, do nothing
                } else {
                    // Write the number of bytes read to the output file
                    fos.write(String.valueOf(bytesRead).getBytes());
                    fos.write("\n".getBytes());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}