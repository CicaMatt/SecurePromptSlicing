import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.zip.CRC32;

public class Checksum {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        String source = "source.txt";
        String destination = "destination.txt";

        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(source)));
        StringBuilder buffer = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            buffer.append(line).append("\n");
        }

        CRC32 crc = new CRC32();
        crc.update(buffer.toString().getBytes(StandardCharsets.UTF_8));
        long checksum = crc.getValue();

        if (checksum == 0) {
            FileOutputStream writer = new FileOutputStream(destination);
            writer.write(buffer.toString().getBytes());
            writer.write(Long.toHexString(checksum).getBytes());
            writer.close();
        }
    }
}