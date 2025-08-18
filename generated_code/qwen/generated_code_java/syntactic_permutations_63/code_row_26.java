import java.io.*;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            int checksum = 0;

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i] & 0xFF;
                    checksum &= 0xFF;
                }
            }

            String result = "Checksum: " + checksum + "\n";
            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}