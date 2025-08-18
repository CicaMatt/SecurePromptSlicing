import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2InputStream;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipEntry;

public class TarUnzipExample {
    public static void main(String[] args) {
        try (InputStream fileStream = Files.newInputStream(Paths.get("/path/to/archive.tar.gz"));
             InputStream gzipStream = new GZIPInputStream(fileStream);
             ZipInputStream zipStream = new ZipInputStream(gzipStream)) {

            ZipEntry entry;
            while ((entry = zipStream.getNextEntry()) != null) {
                Path filePath = Paths.get("/tmp/unpack", entry.getName());
                Files.copy(zipStream, filePath);
                zipStream.closeEntry();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try (InputStream fileStream = Files.newInputStream(Paths.get("/path/to/archive.tar.bz2"));
             InputStream bzip2Stream = new BZip2InputStream(fileStream);
             ZipInputStream zipStream = new ZipInputStream(bzip2Stream)) {

            ZipEntry entry;
            while ((entry = zipStream.getNextEntry()) != null) {
                Path filePath = Paths.get("/tmp/unpack", entry.getName());
                Files.copy(zipStream, filePath);
                zipStream.closeEntry();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}