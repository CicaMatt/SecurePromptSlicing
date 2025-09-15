import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try (TarInputStream tis = new TarInputStream(new GZIPInputStream(new FileInputStream(tarFilePath)))) {
            TarEntry entry;
            while ((entry = tis.getNextEntry()) != null) {
                Path destinationPath = Paths.get(destDirectory, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destinationPath);
                } else {
                    Files.createDirectories(destinationPath.getParent());
                    try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(destinationPath.toFile()))) {
                        byte[] buffer = new byte[1024];
                        int read;
                        while ((read = tis.read(buffer)) != -1) {
                            bos.write(buffer, 0, read);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
