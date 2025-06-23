java 
import java.io.*;
import java.nio.charset.StandardCharsets;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.io.FileUtils;

class CodeGenerator{
    public static void main(String[] args) throws IOException {
        try (TarArchiveInputStream tais = new TarArchiveInputStream(new FileInputStream("/path/to/file"))) {
            TarArchiveEntry entry = null;
            while ((entry = tais.getNextTarEntry()) != null) {
                if (!entry.isDirectory()) {
                    byte[] data = new byte[(int) entry.getSize()];
                    FileUtils.copyInputStreamToFile(new ByteArrayInputStream(data), new File("/tmp/unpack/" + entry.getName()));
                }
            }
        } 
    }
}