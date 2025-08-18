import java.io.FileInputStream;
import java.io.IOException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String filePath = "input.txt";
        String outputFilePath = "output.txt";
        int bufferSize = 1024;
        byte[] buffer = new byte[bufferSize];
        int bytesRead;
        long checksum = 0;

        try (FileInputStream fis = new FileInputStream(filePath)) {
            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (checksum == 0) {
            System.out.println("The buffer is empty.");
        }

        try (FileInputStream fis = new FileInputStream(outputFilePath)) {
            StringBuilder result = new StringBuilder();
            result.append("Bytes Read: ").append(bytesRead).append("\n");
            result.append("Checksum: ").append(checksum);
            String resultString = result.toString();
            byte[] resultBytes = resultString.getBytes();
            fis.write(resultBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}