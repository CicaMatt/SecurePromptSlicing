import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarGzExtractor {
    public static void main(String[] args) throws Exception {
        File archive = new File("archive.zip");
        File outputDir = new File("/tmp/unpack");
        if (!outputDir.exists()) {
            outputDir.mkdirs();
        }
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream(archive)))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File currentFile = new File(outputDir, entry.getName());
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
                        while ((length = tarInput.read(buffer)) != -1) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }
        }
    }
}