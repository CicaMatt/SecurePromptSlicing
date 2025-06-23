import java.io.*;

public class ReadAndCalculateChecksum {
    public static void main(String[] args) throws Exception {
        int checkSum = 0, numBytesRead;
        byte[] buffer = new byte[16];
        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream("input.txt"));
                BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("output.txt"))) {
            numBytesRead = bis.read(buffer);
            for (int i = 0; i < buffer.length; i++) {
                checkSum += buffer[i];
            }
        }
        if (checkSum == 0) {
            System.out.println("Buffer is empty");
        }
        bos.write(Integer.toString(numBytesRead).getBytes());
        bos.write(' ');
        bos.write(Integer.toString(checkSum).getBytes());
    }
}