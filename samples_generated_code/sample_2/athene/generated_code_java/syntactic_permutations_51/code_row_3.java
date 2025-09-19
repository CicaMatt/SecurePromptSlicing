import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2InputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz"; // or .tar.bz2
        String outputDirPath = "/tmp/unpack";

        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(
                new FileInputStream(tarFilePath),
                getCompressionInputStream(new FileInputStream(tarFilePath)))) {

            File outputDir = new File(outputDirPath);
            if (!outputDir.exists()) {
                Files.createDirectories(Paths.get(outputDirPath));
            }

            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                Path entryPath = Paths.get(outputDirPath, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.copy(tarInput, entryPath);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static java.io.InputStream getCompressionInputStream(FileInputStream fis) throws Exception {
        String fileName = new File(fis.toString()).getName().toLowerCase();
        if (fileName.endsWith(".gz")) {
            return new GZIPInputStream(fis);
        } else if (fileName.endsWith(".bz2")) {
            return new BZip2InputStream(fis);
        }
        return fis;
    }
}