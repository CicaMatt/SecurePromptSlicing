import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;

public class ExtractTarGz {
    public static void main(String[] args) {
        File tarFile = new File("archive.zip");
        String outputDirPath = "/tmp/unpack";

        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new GzipCompressorInputStream(new FileInputStream(tarFile)))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                if (entry.isDirectory()) {
                    continue;
                }
                File curFile = new File(outputDirPath, entry.getName());
                File parent = curFile.getParentFile();
                if (!parent.exists()) {
                    parent.mkdirs();
                }
                org.apache.commons.io.FileUtils.copyInputStreamToFile(tarInput, curFile);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}