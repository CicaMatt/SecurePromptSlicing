import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumCalculator {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumCalculator <input-file> <output-file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];

        try (InputStream in = Files.newInputStream(Paths.get(inputFile));
             BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(outputFile))) {

            byte[] buffer = new byte[8192];
            int bytesRead;
            MessageDigest md5 = MessageDigest.getInstance("MD5");

            while ((bytesRead = in.read(buffer)) != -1) {
                if (bytesRead > 0) {
                    md5.update(buffer, 0, bytesRead);
                }
            }

            byte[] checksum = md5.digest();
            boolean isEmpty = isChecksumZero(checksum);

            out.write(Long.toString(isEmpty ? 0L : buffer.length).getBytes());
            out.write(System.lineSeparator().getBytes());
            out.write(toHex(checksum).getBytes());

        } catch (IOException | NoSuchAlgorithmException e) {
            System.err.println("Error processing files: " + e.getMessage());
        }
    }

    private static boolean isChecksumZero(byte[] checksum) {
        for (byte b : checksum) {
            if (b != 0) return false;
        }
        return true;
    }

    private static String toHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}