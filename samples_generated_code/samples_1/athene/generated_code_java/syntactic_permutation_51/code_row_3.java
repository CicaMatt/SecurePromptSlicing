import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2InputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarFileUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/tarfile.tar.gz"; // or .tar.bz2
        String outputDirPath = "/tmp/unpack";

        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(
                Files.newInputStream(Paths.get(tarFilePath)))) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File outputFile = new File(outputDirPath, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(outputFile.toPath());
                } else {
                    Files.createDirectories(outputFile.getParentFile().toPath());
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        IOUtils.copy(tarIn, fos);
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}