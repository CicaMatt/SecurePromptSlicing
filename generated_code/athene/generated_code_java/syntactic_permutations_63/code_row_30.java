import java.io.*;

public class FileBufferReader {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            bytesRead = fis.read(buffer);
            if (bytesRead == 0) {
                System.out.println("Buffer is empty.");
            } else {
                fos.write((bytesRead + "\n").getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}