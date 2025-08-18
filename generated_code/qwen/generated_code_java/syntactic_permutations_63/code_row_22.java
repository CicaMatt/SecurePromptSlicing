import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            int byteRead;
            long checksum = 0;
            int bytesReadCount = 0;

            while ((byteRead = fis.read()) != -1) {
                checksum += byteRead;
                bytesReadCount++;
            }

            if (checksum == 0) {
                System.out.println("The file is empty.");
            }

            String result = "Bytes read: " + bytesReadCount + "\nChecksum: " + checksum;
            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}