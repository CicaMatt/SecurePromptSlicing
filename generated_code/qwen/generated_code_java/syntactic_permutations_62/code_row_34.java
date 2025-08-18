import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String filePath = "input.txt"; // Change this to your file path
        byte[] buffer = new byte[8192]; // Buffer size
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            String resultFilePath = "result.txt"; // Change this to your desired output file path
            try (java.io.FileWriter fw = new java.io.FileWriter(resultFilePath)) {
                fw.write("Bytes read: " + fis.getChannel().size() + "\n");
                fw.write("Checksum: " + checksum);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}