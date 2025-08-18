import java.io.InputStream;
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
        try (InputStream fileIn = Files.newInputStream(Paths.get("/path/to/archive.tar.gz"));
             InputStream gzipIn = new GZIPInputStream(fileIn);
             TarArchiveInputStream tarIn = new TarArchiveInputStream(gzipIn)) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                Path entryPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    try (InputStream entryData = tarIn) {
                        Files.copy(entryData, entryPath);
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}