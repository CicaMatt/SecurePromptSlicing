import java.io.*;
import java.nio.file.*;

public class CheckSum {
    public static void main(String[] args) throws Exception {
        String inputFile = "input_file";
        String outputFile = "output_file";
        byte[] buffer = new byte[1024];
        int checksum = 0;
        try (InputStream in = new FileInputStream(inputFile);
                OutputStream out = new FileOutputStream(outputFile)) {
            int bytesRead;
            while ((bytesRead = in.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }
        }
        out.write((Integer.toString(checksum) + "\n" + Integer.toString(bytesRead)).getBytes());
        if (checksum == 0) {
            System.out.println("Buffer is empty");
        } else {
            System.out.println("Checksum: " + checksum);
            System.out.println("Number of bytes read: " + bytesRead);
        }
    }
}