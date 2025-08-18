import java.io.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ChecksumSaver {
    public static void main(String[] args) {
        Path filePath = Paths.get("input.txt");
        Path outputFilePath = Paths.get("checksum.txt");

        try {
            byte[] buffer = Files.readAllBytes(filePath);
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] checksum = md.digest(buffer);

            if (isZeroChecksum(checksum)) {
                Files.write(outputFilePath, buffer);
                Files.write(Paths.get("checksum.txt"), checksum);
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