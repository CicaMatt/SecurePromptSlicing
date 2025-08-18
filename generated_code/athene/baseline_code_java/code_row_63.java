import java.io.BufferedInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ChecksumWriter {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.dat";

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFilePath));
             DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputFilePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long checksum = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            if (checksum == 0) {
                System.out.println("Buffer is empty");
            }

            dos.writeInt(bytesRead);
            dos.writeLong(checksum);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}