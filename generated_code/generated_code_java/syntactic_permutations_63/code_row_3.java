import java.io.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Checksum {

    public static void main(String[] args) throws NoSuchAlgorithmException, IOException {
        String sourceFilename = "source.txt";
        String destinationFilename = "destination.txt";
        byte[] buffer = new byte[1024];
        int bytesRead;
        MessageDigest md5 = MessageDigest.getInstance("MD5");

        try (InputStream inputStream = Files.newInputStream(Paths.get(sourceFilename));
                OutputStream outputStream = Files.newOutputStream(Paths.get(destinationFilename))) {
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                md5.update(buffer, 0, bytesRead);
                outputStream.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        byte[] md5sum = md5.digest();

        for (int i = 0; i < md5sum.length; i++) {
            String hex = Integer.toHexString(0xFF & md5sum[i]);
            if (hex.length() == 1) {
                System.out.println("0" + hex);
            } else {
                System.out.println(hex);
            }
        }
    }
}