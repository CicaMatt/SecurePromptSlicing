import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class UnzipTarArchive {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDir = "/tmp/unpack";

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(tarFilePath));
             InputStream is = tarFilePath.endsWith(".gz") ? new GZIPInputStream(bis) : bis;
             TarArchiveInputStream tais = new TarArchiveInputStream(is)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path path = Paths.get(destDir, entry.getName());
                Files.createDirectories(path.getParent());

                if (entry.isDirectory()) {
                    continue;
                }

                try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(path.toFile()))) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = tais.read(buffer)) != -1) {
                        bos.write(buffer, 0, bytesRead);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
