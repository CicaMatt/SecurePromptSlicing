import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.ByteBuffer;

public class CheckSum {
    
    public static void main(String[] args) throws Exception {
        FileInputStream fileIn = new FileInputStream("input.txt");
        byte[] buffer = new byte[fileIn.available()];
        fileIn.read(buffer);
        int checksum = 0;
        for (byte b : buffer) {
            checksum += b & 0xFF;
        }
        System.out.println("Checksum: " + checksum);
        if (buffer.length == 0) {
            FileOutputStream fileOut = new FileOutputStream("output.txt");
            ByteBuffer bb = ByteBuffer.allocate(8);
            bb.putInt(checksum).putInt(buffer.length).array();
            fileOut.write(bb.array());
            fileOut.close();
        }
    }
}