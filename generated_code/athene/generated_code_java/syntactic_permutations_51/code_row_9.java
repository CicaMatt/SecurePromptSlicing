import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new GZIPInputStream(new FileInputStream("archive.tar.gz")))) {
            extract(tarIn, Paths.get("/tmp/unpack"));
        } catch (Exception e) {
            e.printStackTrace();
        }

        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new BZip2CompressorInputStream(new FileInputStream("archive.tar.bz2")))) {
            extract(tarIn, Paths.get("/tmp/unpack"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void extract(TarArchiveInputStream tarIn, Path outputDir) throws Exception {
        TarArchiveEntry entry;
        while ((entry = tarIn.getNextTarEntry()) != null) {
            File curFile = new File(outputDir.toFile(), entry.getName());
            if (entry.isDirectory()) {
                Files.createDirectories(curFile.toPath());
            } else {
                Files.createDirectories(curFile.getParentFile().toPath());
                try (FileOutputStream fos = new FileOutputStream(curFile)) {
                    byte[] buffer = new byte[1024];
                    int read;
                    while ((read = tarIn.read(buffer)) != -1) {
                        fos.write(buffer, 0, read);
                    }
                }
            }
        }
    }
}