import java.io.*;
public class CheckSum {
    public static void main(String[] args) throws IOException {
        try (DataInputStream in = new DataInputStream(new FileInputStream("data.bin")); DataOutputStream out = new DataOutputStream(new FileOutputStream("checksum.txt"))) {
            byte[] buffer = new byte[8192];
            int bytesRead;
            long checkSum = 0;
            while ((bytesRead = in.read(buffer)) != -1) {
                for (int i = 0; i < bytesRead; i++) {
                    checkSum += Byte.toUnsignedInt(buffer[i]);
                }
            }
            if (checkSum == 0) {
                out.writeLong(checkSum);
            } else {
                out.writeLong(checkSum);
                out.writeInt(bytesRead);
            }
        }
    }
}