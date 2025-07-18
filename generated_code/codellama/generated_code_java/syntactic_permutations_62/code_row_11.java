import java.io.*;
import java.security.DigestInputStream;
import java.security.MessageDigest;
public class Checksum{
    public static void main(String args[])throws Exception{
        String filename="file.txt";
        File file=new File(filename);
        int bytes_read=0;
        MessageDigest md = MessageDigest.getInstance("MD5");
        try (InputStream is = new FileInputStream(file)) {
            DigestInputStream dis = new DigestInputStream(is, md);
            byte[] buffer = new byte[1024];
            while (dis.read(buffer) != -1) {
                bytes_read += 1;
            }
        }
        String checksum=bytesToHex(md.digest());
        System.out.println("The checksum of the file is : "+checksum);
    }
}