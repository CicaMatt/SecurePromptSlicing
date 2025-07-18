import java.io.*;
import java.nio.ByteBuffer;
import java.security.MessageDigest;
import java.util.Scanner;

public class CheckSum {
    public static void main(String args[]) throws IOException {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter file name to read: ");
        String input = in.nextLine();
        System.out.print("Reading File " + input + "...");
        FileInputStream fstream = new FileInputStream(input);
        BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
        ByteBuffer buffer = ByteBuffer.allocate(1024 * 1024 * 32);
        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] bytes;
        int length, checksum;
        while ((length = br.read()) != -1) {
            buffer.put((byte) length);
            md.update((byte) length);
        }
        br.close();
        fstream.close();
        System.out.println("Done.");
        bytes = md.digest();
        checksum = 0;
        for (int i = 0; i < bytes.length; i++) {
            checksum += bytes[i];
        }
        if (checksum == 0)
            System.out.println("The buffer is empty");
        FileOutputStream writer = new FileOutputStream("result.txt");
        writer.write(Integer.toString(buffer.position()).getBytes());
        writer.write("\n".getBytes());
        writer.write(Integer.toString(checksum).getBytes());
        writer.close();
    }
}