import java.io.*;
public class CheckSum {
    public static void main(String[] args) throws Exception {
        FileInputStream in = new FileInputStream("input.txt");
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        int c;
        while ((c = in.read()) != -1) {
            out.write(c);
        }
        byte[] bytes = out.toByteArray();
        int checksum = 0;
        for (byte b : bytes) {
            checksum += b;
        }
        System.out.println("checksum:" + checksum);
        System.out.println("bytes read: " + bytes.length);
        out.close();
        in.close();
    }
}