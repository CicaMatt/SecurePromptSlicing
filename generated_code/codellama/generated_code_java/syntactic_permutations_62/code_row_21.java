import java.io.*;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
 
public class CheckSumCalculator {
	
    public static void main(String args[]) {
        String filename = "sample.txt";
        FileInputStream fileInputStream = null;
        try {
            // Open the file that is the first command line parameter
            fileInputStream = new FileInputStream(filename);
 
            FileChannel channel = fileInputStream.getChannel();
            ByteBuffer buffer = ByteBuffer.allocate((int) channel.size());
            channel.read(buffer);
            byte[] bytesArray = buffer.array(); // The bytes you want to calculate the checksum for are here
 
            int sum = 0;
            for (byte b : bytesArray) {
                sum += b;
            }
            System.out.println(sum);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                fileInputStream.close();
            } catch (Exception e) {
            }
        }
    }
}