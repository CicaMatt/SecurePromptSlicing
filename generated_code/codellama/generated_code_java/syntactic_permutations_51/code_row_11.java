import java.io.FileInputStream;
import java.io.IOException;
import java.util.Enumeration;

import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.io.FileUtils;

public class Unpack {
    public static void main(String[] args) throws IOException {
        try (TarArchiveInputStream tarStream = new TarArchiveInputStream(new FileInputStream("example.tar.gz"))) {
            TarArchiveEntry entry;
            while ((entry = tarStream.getNextTarEntry()) != null) {
                if (!entry.isFile()) {
                    continue;
                }
                System.out.println(entry);
                FileUtils.copyInputStreamToFile(tarStream, new File("/tmp/unpack/" + entry.getName()));
            }
        }
    }
}