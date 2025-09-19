import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz";
        String extractPath = "/tmp/unpack";

        File destinationDir = new File(extractPath);
        if (!destinationDir.exists()) {
            destinationDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GZIPInputStream gis = new GZIPInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File outputFile = new File(destinationDir, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) != -1) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
