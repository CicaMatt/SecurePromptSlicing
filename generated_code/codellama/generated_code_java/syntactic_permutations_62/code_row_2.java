import java.io.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Formatter;

public class Checksum {

    public static void main(String[] args) throws NoSuchAlgorithmException, IOException {
        String inputPath = "input.txt";
        String outputPath = "output.txt";
        
        File inputFile = new File(inputPath);
        byte[] buffer = readFully(inputFile);

        MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
        messageDigest.update(buffer);
        byte[] checksum = messageDigest.digest();

        Formatter formatter = new Formatter();
        for (byte b : checksum) {
            formatter.format("%02x", b);
        }
        
        File outputFile = new File(outputPath);
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputFile), StandardCharsets.UTF_8));
        String checksumHexString = formatter.toString();
        
        if (checksumHexString.equals("0")) {
            writer.write("The buffer is empty.");
        } else {
            int bytesRead = buffer.length;
            writer.write(Integer.toString(bytesRead));
            writer.newLine();
            writer.write(checksumHexString);
        }
        
        writer.close();
    }
    
    public static byte[] readFully(File file) throws IOException {
        FileInputStream inputStream = new FileInputStream(file);
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        int read;
        while ((read = inputStream.read()) != -1) {
            output.write(read);
        }
        
        byte[] bytes = output.toByteArray();
        return bytes;
    }
}