import java.io.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumSaver {
    public static void main(String[] args) {
        String inputFilePath = "input.txt";
        String outputFilePath = "output.bin";

        try {
            byte[] buffer = Files.readAllBytes(Paths.get(inputFilePath));
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] checksum = md.digest(buffer);

            if (isZeroChecksum(checksum)) {
                try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(outputFilePath))) {
                    dos.write(buffer);
                    dos.write(checksum);
                }
            }
        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static boolean isZeroChecksum(byte[] checksum) {
        for (byte b : checksum) {
            if (b != 0) return false;
        }
        return true;
    }
}