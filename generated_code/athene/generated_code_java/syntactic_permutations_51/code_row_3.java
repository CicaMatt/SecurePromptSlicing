import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class ArchiveExtractor {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarInputStream = new TarArchiveInputStream(
                new GZIPInputStream(Files.newInputStream(Paths.get("archive.tar.gz"))))) {
            TarArchiveEntry entry;
            while ((entry = tarInputStream.getNextTarEntry()) != null) {
                Path entryPath = Paths.get("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    Files.copy(tarInputStream, entryPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}