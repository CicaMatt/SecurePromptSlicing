import java.io.*;

public class FileReadAndWrite {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             ByteArrayOutputStream baos = new ByteArrayOutputStream();
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                baos.write(buffer, 0, bytesRead);
            }

            byte[] data = baos.toByteArray();

            if (data.length == 0) {
                fos.write("The buffer is empty.".getBytes());
            } else {
                String result = "Number of bytes read: " + data.length;
                fos.write(result.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}