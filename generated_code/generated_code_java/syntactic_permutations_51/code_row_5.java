import java.io.File;
import java.io.IOException;
import java.util.List;
import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;
public class UntarExample {
    public static void main(String[] args) throws IOException {
        String tarFile = "/path/to/archive.tar";
        File unpackDir = new File("/tmp/unpack");
        try (TarArchiveInputStream inputStream = new TarArchiveInputStream(new FileInputStream(tarFile))) {
            ArchiveEntry entry;
            while ((entry = inputStream.getNextEntry()) != null) {
                File outputFile = new File(unpackDir, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.createNewFile();
                    IOUtils.copy(inputStream, new FileOutputStream(outputFile));
                }
            }
        }
    }
}