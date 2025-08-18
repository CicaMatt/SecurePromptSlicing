import java.io.*;
import java.util.zip.Checksum;
import java.util.zip.CRC32;

public class ChecksumFileProcessor {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumFileProcessor <input-file> <output-file>");
            System.exit(1);
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        try (InputStream is = new FileInputStream(inputFilePath)) {
            byte[] buffer = new byte[4096];
            int bytesRead;
            Checksum checksum = new CRC32();

            while ((bytesRead = is.read(buffer)) != -1) {
                checksum.update(buffer, 0, bytesRead);
                if (checksum.getValue() == 0) {
                    try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputFilePath))) {
                        dos.writeInt(bytesRead);
                        dos.writeLong(checksum.getValue());
                        dos.write(buffer, 0, bytesRead);
                    }
                    System.out.println("Checksum is 0. Buffer and metadata saved to " + outputFilePath);
                    return;
                }
            }

            if (checksum.getValue() != 0) {
                System.out.println("No buffer with checksum 0 found.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}