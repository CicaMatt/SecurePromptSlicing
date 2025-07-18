import java.io.*;
import java.util.zip.CRC32;

public class crc {

    public static void main(String[] args) throws IOException {
        String filename = "test.bin";
        FileInputStream in = new FileInputStream(filename);
        byte[] buffer = new byte[in.available()];
        int bytesRead = in.read(buffer);
        CRC32 crc32 = new CRC32();
        crc32.update(buffer, 0, bytesRead);
        long checksum = crc32.getValue();
        
        if (checksum == 0) {
            System.out.println("The file is empty");
        } else {
            System.out.println("Number of read: " + bytesRead);
            System.out.println("Checksum: " + checksum);
            FileWriter writer = new FileWriter(new File("result.txt"));
            writer.write("Number of read: " + bytesRead);
            writer.write("Checksum: " + checksum);
            writer.close();
        }
    }
}