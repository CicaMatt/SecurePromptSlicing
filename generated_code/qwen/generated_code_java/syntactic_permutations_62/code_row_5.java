import java.io.*;

public class ChecksumCalculator {
    public static void main(String[] args) {
        byte[] buffer = new byte[1024];
        int bytesRead;
        int checksum = 0;

        try (InputStream inputStream = System.in;
             OutputStream outputStream = new FileOutputStream("output.txt")) {

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checksum += buffer[i];
                }
            }

            if (checksum == 0 && bytesRead == 0) {
                outputStream.write("Buffer is empty.\n".getBytes());
            } else {
                String result = "Bytes read: " + bytesRead + ", Checksum: " + checksum + "\n";
                outputStream.write(result.getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}