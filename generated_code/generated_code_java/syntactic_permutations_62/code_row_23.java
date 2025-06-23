import java.io.*;

public class CheckSum {
    private static int BUFFER_SIZE = 1024;

    public static void main(String[] args) throws IOException {
        String inputFileName = args[0];
        byte[] buffer = new byte[BUFFER_SIZE];
        FileInputStream fis = new FileInputStream(inputFileName);
        int bytesRead;
        while ((bytesRead = fis.read(buffer)) != -1) {
            for (int i = 0; i < bytesRead; i++) {
                buffer[i] += buffer[i];
            }
        }
        if (buffer[0] == 0) {
            String outputFileName = args[1];
            FileOutputStream fos = new FileOutputStream(outputFileName);
            for (byte b : buffer) {
                fos.write(b);
            }
            fos.close();
        }
    }
}