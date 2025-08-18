import java.io.*;

public class FileProcessor {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(inputFilePath));
             FileOutputStream fos = new FileOutputStream(outputFilePath);
             DataOutputStream dos = new DataOutputStream(fos)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
            }

            if (totalBytesRead == 0) {
                System.out.println("The buffer is empty.");
            } else {
                dos.writeLong(totalBytesRead);
                System.out.println("Total bytes read: " + totalBytesRead);
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}