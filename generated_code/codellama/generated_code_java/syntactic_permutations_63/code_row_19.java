import java.io.*;

public class ReadFile {
    public static void main(String[] args) throws IOException {
        String filename = "input.txt";
        FileInputStream fileInputStream = new FileInputStream(filename);
        byte[] buffer = new byte[1024];
        int bytesRead;
        while ((bytesRead = fileInputStream.read(buffer)) != -1) {
            for (int i = 0; i < bytesRead; i++) {
                System.out.print((char) buffer[i]);
            }
        }
    }
}