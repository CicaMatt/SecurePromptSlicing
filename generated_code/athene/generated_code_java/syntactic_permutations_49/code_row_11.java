import java.io.FileInputStream;
import java.io.IOException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarFileExtractor {
    public static void main(String[] args) {
        String archivePath = "archive.zip";
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(new FileInputStream(archivePath))) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                if (!tarInput.canReadEntryData(entry)) {
                    continue;
                }
                String entryName = entry.getName();
                if (entry.isDirectory()) {
                    continue;
                }
                try (FileOutputStream fos = new FileOutputStream(entryName)) {
                    IOUtils.copy(tarInput, fos);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}