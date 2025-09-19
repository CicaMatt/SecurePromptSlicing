import java.io.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        byte[] buffer = new byte[1024];
        int bytesRead;
        long checksumValue = 0;

        try (InputStream is = new FileInputStream(inputFilePath);
             Checksum checksum = new CRC32()) {

            while ((bytesRead = is.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
                checksumValue = checksum.getValue();
            }

            if (checksumValue == 0 && bytesRead == -1) {
                System.out.println("Buffer is empty");
            } else {
                try (FileWriter fw = new FileWriter(outputFilePath)) {
                    fw.write("Bytes Read: " + bytesRead + "\n");
                    fw.write("Checksum: " + checksumValue);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}