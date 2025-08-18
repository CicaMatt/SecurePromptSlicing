import java.io.*;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            int bytesRead;
            int checksum = 0;
            byte[] buffer = new byte[1024];

            while ((bytesRead = fis.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0) {
                fos.write("Buffer is empty.".getBytes());
            } else {
                String result = "Bytes read: " + fis.getChannel().size() + "\nChecksum: " + checksum;
                fos.write(result.getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}