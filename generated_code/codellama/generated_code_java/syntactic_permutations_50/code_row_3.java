import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Decompressor {
    public static void main(String[] args) throws IOException {
        // create a tar file
        File tarFile = new File("archive.tar");
        if (!tarFile.exists()) return;
        
        // extract the files
        try (TarArchiveInputStream is = new TarArchiveInputStream(new GZIPInputStream(new FileInputStream(tarFile)))) {
            for (TarArchiveEntry entry = null; (entry = is.getNextTarEntry()) != null;) {
                if (!entry.isDirectory()) {
                    byte[] buffer = new byte[(int) entry.getSize()];
                    int read = 0;
                    while (read < buffer.length) read += is.read(buffer, read, buffer.length - read);
                    Files.write(Paths.get("/tmp/unpack/" + entry.getName()), buffer);
                }
            }
        } catch (IOException e) {
            System.out.println("Exception while untarring: " + e);
        }
    }
}