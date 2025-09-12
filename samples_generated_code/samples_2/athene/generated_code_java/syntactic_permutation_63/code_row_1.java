import java.io.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumFileProcessor {
    public static void main(String[] args) {
        String inputFile = "input.txt";
        String outputFile = "output.txt";

        try (InputStream in = new FileInputStream(inputFile);
             OutputStream out = new FileOutputStream(outputFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            Checksum checksum = new CRC32();

            while ((bytesRead = in.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
            }

            long calculatedChecksum = checksum.getValue();
            boolean isEmpty = (calculatedChecksum == 0);

            try (DataOutputStream dataOut = new DataOutputStream(out)) {
                dataOut.writeInt(bytesRead);
                dataOut.writeLong(calculatedChecksum);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}