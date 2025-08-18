import java.io.*;

public class ChecksumCalculator {
    public static void main(String[] args) {
        String inputFileName = "input.bin";
        String outputFileName = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFileName);
             FileOutputStream fos = new FileOutputStream(outputFileName)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            int checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                }
            }

            if (checksum == 0 && bytesRead == 0) {
                fos.write("Buffer is empty.\n".getBytes());
            } else {
                String result = "Bytes read: " + bytesRead + ", Checksum: " + checksum + "\n";
                fos.write(result.getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}