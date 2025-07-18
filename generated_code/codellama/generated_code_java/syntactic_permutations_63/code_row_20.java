import java.io.*;
import java.util.*;
import java.nio.file.*;
public class ReadAndCheckSum {
    public static void main(String[] args) throws IOException {
        String filename = "my-data.txt";
        byte[] buffer = Files.readAllBytes(Paths.get(filename));
        int checksum = 0;
        for (byte b : buffer) checksum += b;
        if (buffer.length == 0) {
            System.out.println("Buffer is empty");
        } else {
            System.out.printf("Read %d bytes, checksum = %d%n", buffer.length, checksum);
            Path outFile = Paths.get("my-data-output.txt");
            Files.write(outFile, String.format("%d:%d", buffer.length, checksum).getBytes());
        }
    }
}