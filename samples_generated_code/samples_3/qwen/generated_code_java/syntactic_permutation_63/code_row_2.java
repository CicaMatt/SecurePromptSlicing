import java.io.*;

public class FileBufferReader {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;

        try (FileInputStream inputStream = new FileInputStream(inputFile);
             FileOutputStream outputStream = new FileOutputStream(outputFile)) {

            bytesRead = inputStream.read(buffer);

            if (bytesRead == 0) {
                System.out.println("The buffer is empty.");
            } else if (bytesRead > 0) {
                outputStream.write(("Number of bytes read: " + bytesRead).getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}