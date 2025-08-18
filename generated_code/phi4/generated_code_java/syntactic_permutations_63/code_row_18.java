import java.io.*;

public class FileProcessor {

    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             BufferedInputStream bis = new BufferedInputStream(fis);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            long totalBytesRead = 0;

            while ((bytesRead = bis.read(buffer)) != -1) {
                totalBytesRead += bytesRead;
            }

            if (totalBytesRead == 0) {
                System.out.println("Buffer is empty.");
            } else {
                fos.write(String.valueOf(totalBytesRead).getBytes());
            }
            
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}