import java.io.*;

public class FileChecksum {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.txt";

        byte[] buffer;
        int bytesRead;
        long checksum;

        try (FileInputStream fis = new FileInputStream(inputFilePath);
             FileOutputStream fos = new FileOutputStream(outputFilePath)) {

            buffer = new byte[1024];
            bytesRead = fis.read(buffer);

            checksum = calculateChecksum(buffer, bytesRead);

            if (checksum == 0) {
                System.out.println("The file is empty.");
            }

            String result = "Bytes Read: " + bytesRead + "\nChecksum: " + checksum;
            fos.write(result.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static long calculateChecksum(byte[] buffer, int length) {
        long sum = 0;
        for (int i = 0; i < length; i++) {
            sum += buffer[i];
        }
        return sum & 0xFFFFFFFFL;
    }
}