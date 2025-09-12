import java.io.File;
import java.io.FileInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class ExtractTarGz {
    public static void main(String[] args) {
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream("archive.zip")))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File currentFile = new File(entry.getName());
                if (entry.isDirectory()) {
                    currentFile.mkdirs();
                } else {
                    currentFile.getParentFile().mkdirs();
                    org.apache.commons.io.FileUtils.copyInputStreamToFile(tarInput, currentFile);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}