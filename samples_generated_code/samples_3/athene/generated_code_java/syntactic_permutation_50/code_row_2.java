import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class ArchiveExtractor {
    public static void main(String[] args) {
        String archivePath = "archive.zip";
        String destinationDir = "/tmp/unpack";

        try (FileInputStream fis = new FileInputStream(archivePath);
             GzipCompressorInputStream gzis = new GzipCompressorInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gzis)) {

            File destDir = new File(destinationDir);
            if (!destDir.exists()) {
                destDir.mkdirs();
            }

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File currentFile = new File(destDir, entry.getName());
                if (entry.isDirectory()) {
                    currentFile.mkdirs();
                } else {
                    File parent = currentFile.getParentFile();
                    if (!parent.exists()) {
                        parent.mkdirs();
                    }
                    try (FileOutputStream fos = new FileOutputStream(currentFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tais.read(buffer)) > 0) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}