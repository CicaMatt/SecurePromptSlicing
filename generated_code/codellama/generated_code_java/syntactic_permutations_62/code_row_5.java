import java.io.*;
import java.util.zip.CRC32;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
public class ReadBuffer {
    public static void main(String[] args) throws IOException, NoSuchAlgorithmException {
        //read into buffer
        byte[] buffer = new byte[1024];
        int bytesRead = System.in.read(buffer);
        //calculate checksum of the buffer
        CRC32 crc = new CRC32();
        MessageDigest md = MessageDigest.getInstance("MD5");
        crc.update(buffer, 0, bytesRead);
        long checkSum = crc.getValue();
        //save number of bytes read and the checksum to a file
        FileWriter writer = new FileWriter("checksum.txt", false);
        writer.write(Long.toString(bytesRead) + "\n" + Long.toHexString(checkSum));
        writer.close();
    }
}