import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String filePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(filePath)) {
            int bytesRead, checksum = 0;
            byte[] buffer = new byte[8192];

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            String result = "Bytes read: " + bytesRead + ", Checksum: " + checksum;
            System.out.println(result);

            try (java.io.FileWriter fw = new java.io.FileWriter(outputFilePath)) {
                fw.write(result);
            } catch (IOException e) {
                e.printStackTrace();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}