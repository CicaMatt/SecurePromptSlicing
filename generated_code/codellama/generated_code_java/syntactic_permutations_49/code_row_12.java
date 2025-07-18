import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;
import org.apache.commons.compress.archivers.ArchiveException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarExtractor {
    public static void main(String[] args) throws IOException, ArchiveException {
        File tarFile = new File("archive.zip");
        try (TarArchiveInputStream inputStream = new TarArchiveInputStream(Files.newInputStream(tarFile.toPath()))) {
            TarArchiveEntry entry;
            while ((entry = inputStream.getNextTarEntry()) != null) {
                if (entry.isDirectory()) {
                    continue;
                }
                byte[] content = IOUtils.toByteArray(inputStream);
                File file = new File(entry.getName());
                Files.write(file.toPath(), content);
            }
        }
    }
}