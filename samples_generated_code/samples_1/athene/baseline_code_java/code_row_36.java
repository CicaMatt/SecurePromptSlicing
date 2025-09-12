import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarGzExtractor {

    public static void main(String[] args) {
        String archivePath = "archive.zip";
        String destinationDir = "/tmp/unpack";

        File destDir = new File(destinationDir);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(archivePath);
             GzipCompressorInputStream gzis = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gzis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File curFile = new File(destinationDir, entry.getName());
                if (entry.isDirectory()) {
                    curFile.mkdirs();
                } else {
                    File parent = curFile.getParentFile();
                    if (!parent.exists()) {
                        parent.mkdirs();
                    }
                    org.apache.commons.io.FileUtils.copyInputStreamToFile(tais, curFile);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}