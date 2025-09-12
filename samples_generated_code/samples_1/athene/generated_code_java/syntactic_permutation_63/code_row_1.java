import java.io.*;
import java.nio.file.*;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        
        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            int checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            if (checksum == 0) {
                System.out.println("The file is empty.");
            }

            fos.write(("Bytes read: " + fis.getChannel().position() + "\n").getBytes());
            fos.write(("Checksum: " + checksum).getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}