import java.io.*;

public class FileChecksum {
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

            if (checksum == 0 && bytesRead == 0) {
                fos.write("Buffer is empty.\n".getBytes());
            } else {
                String result = "Number of bytes read: " + bytesRead + "\nChecksum: " + checksum + "\n";
                fos.write(result.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}