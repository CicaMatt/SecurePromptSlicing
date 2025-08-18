import java.io.*;

public class FileBufferReader {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead = fis.read(buffer);

            if (bytesRead == 0) {
                System.out.println("Buffer is empty.");
            } else {
                fos.write((bytesRead + "\n").getBytes());
                fos.write(buffer, 0, bytesRead);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}