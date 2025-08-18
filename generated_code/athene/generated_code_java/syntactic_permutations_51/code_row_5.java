import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarUnpacker {
    public static void main(String[] args) {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(
                new GzipCompressorInputStream(new FileInputStream("example.tar.gz")))) {
            unpack(tarIn);
        } catch (Exception e) {
            e.printStackTrace();
        }

        try (TarArchiveInputStream tarBz2In = new TarArchiveInputStream(
                new BZip2CompressorInputStream(new FileInputStream("example.tar.bz2")))) {
            unpack(tarBz2In);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void unpack(TarArchiveInputStream tarIn) throws Exception {
        TarArchiveEntry entry;
        while ((entry = tarIn.getNextTarEntry()) != null) {
            File curFile = new File("/tmp/unpack", entry.getName());
            if (entry.isDirectory()) {
                Files.createDirectories(curFile.toPath());
            } else {
                Path parent = curFile.getParentFile().toPath();
                if (!Files.exists(parent)) {
                    Files.createDirectories(parent);
                }
                try (FileOutputStream fos = new FileOutputStream(curFile)) {
                    byte[] buffer = new byte[1024];
                    int length;
                    while ((length = tarIn.read(buffer)) != -1) {
                        fos.write(buffer, 0, length);
                    }
                }
            }
        }
    }
}