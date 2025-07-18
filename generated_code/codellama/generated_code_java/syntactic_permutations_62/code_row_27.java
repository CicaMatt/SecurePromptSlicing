java
import java.io.*;
import java.nio.file.*;
import java.util.zip.*;

public class Checksum {
    public static void main(String[] args) throws Exception{
        File sourceFile = new File("input.txt");
        Path targetPath = Paths.get("output.txt");

        byte[] buffer;
        int checksum;
        try (InputStream inputStream = new CheckedInputStream(new FileInputStream(sourceFile), new CRC32());) {
            buffer = new byte[100];
            while (inputStream.read(buffer) != -1);
            checksum = ((CheckedInputStream) inputStream).getChecksum().getValue();
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }

        if (checksum == 0) {
            System.out.println("Buffer is empty");
        } else {
            try (OutputStream outputStream = new FileOutputStream(targetPath)) {
                byte[] bytesToWrite = Integer.toString(checksum).getBytes();
                outputStream.write(bytesToWrite);
            } catch (IOException e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }
}