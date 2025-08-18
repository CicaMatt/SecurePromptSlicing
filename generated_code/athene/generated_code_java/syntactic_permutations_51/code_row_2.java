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
        String tarFilePath = "example.tar.gz"; // or .tar.bz2
        String outputDirPath = "/tmp/unpack";

        try (TarArchiveInputStream tarIn = getTarInputStream(new File(tarFilePath))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                Path entryPath = Paths.get(outputDirPath, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    Files.createDirectories(entryPath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(entryPath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarIn.read(buffer)) != -1) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarInputStream(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            if (file.getName().endsWith(".gz")) {
                return new TarArchiveInputStream(new GZIPInputStream(fis));
            } else if (file.getName().endsWith(".bz2")) {
                return new TarArchiveInputStream(new BZip2CompressorInputStream(fis));
            } else {
                return new TarArchiveInputStream(fis);
            }
        }
    }
}