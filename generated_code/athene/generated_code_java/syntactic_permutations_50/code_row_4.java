import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz";
        File outputDir = new File("/tmp/unpack");
        if (!outputDir.exists()) {
            outputDir.mkdirs();
        }
        try (TarArchiveInputStream tais = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream(tarFilePath)))) {
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File curFile = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    curFile.mkdirs();
                } else {
                    File parent = curFile.getParentFile();
                    if (!parent.exists()) {
                        parent.mkdirs();
                    }
                    try (FileOutputStream fos = new FileOutputStream(curFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tais.read(buffer)) != -1) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}