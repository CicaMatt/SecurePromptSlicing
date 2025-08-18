import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        int checksum = 0;
        int bytesRead = 0;
        byte[] buffer = new byte[1024];

        try (FileInputStream fis = new FileInputStream(inputFilePath)) {
            int read;
            while ((read = fis.read(buffer)) != -1) {
                for (int i = 0; i < read; i++) {
                    checksum += buffer[i];
                }
                bytesRead += read;
            }

            if (checksum == 0) {
                System.out.println("The file is empty.");
            }

            try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                fos.write((bytesRead + "\n").getBytes());
                fos.write((checksum + "\n").getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}