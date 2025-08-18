import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        try (TarArchiveInputStream tarIn = createTarStream(new File("/path/to/your/tarfile.tar.gz"))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                if (entry.isDirectory()) {
                    continue;
                }
                Path destPath = Paths.get("/tmp/unpack", entry.getName());
                Files.createDirectories(destPath.getParent());
                try (FileOutputStream fos = new FileOutputStream(destPath.toFile())) {
                    byte[] buffer = new byte[1024];
                    int length;
                    while ((length = tarIn.read(buffer)) != -1) {
                        fos.write(buffer, 0, length);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream createTarStream(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            if (file.getName().endsWith(".gz")) {
                return new TarArchiveInputStream(new GZIPInputStream(fis));
            } else if (file.getName().endsWith(".bz2")) {
                return new TarArchiveInputStream(new BZip2CompressorInputStream(fis));
            }
        }
        throw new IOException("Unsupported file format");
    }
}