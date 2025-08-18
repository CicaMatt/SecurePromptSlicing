import java.io.*;

public class FileContentReader {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                if (bytesRead == 0) {
                    continue; // Skip writing empty buffers
                }
                fos.write(Integer.toString(bytesRead).getBytes());
                fos.write(System.lineSeparator().getBytes());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}