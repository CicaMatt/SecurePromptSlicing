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

        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(
                new FileInputStream(new File(tarFilePath)),
                getCompressionInputStream(new FileInputStream(new File(tarFilePath))))) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarArchiveEntry()) != null) {
                Path outputPath = Paths.get(outputDirPath, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(outputPath);
                } else {
                    Files.createDirectories(outputPath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(outputPath.toFile())) {
                        IOUtils.copy(tarIn, fos);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static InputStream getCompressionInputStream(FileInputStream fis) throws Exception {
        String fileName = fis.getChannel().toString();
        if (fileName.endsWith(".gz")) {
            return new GZIPInputStream(fis);
        } else if (fileName.endsWith(".bz2")) {
            return new BZip2InputStream(fis);
        }
        return fis;
    }
}