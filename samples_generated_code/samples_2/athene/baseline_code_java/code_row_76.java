import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        File inputFile = new File("input.dat");
        File outputFile = new File("output.txt");

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0) {
                System.out.println("The buffer is empty.");
            } else {
                fos.write(("Bytes read: " + fis.getChannel().position() + "\n").getBytes());
                fos.write(("Checksum: " + checksum + "\n").getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}