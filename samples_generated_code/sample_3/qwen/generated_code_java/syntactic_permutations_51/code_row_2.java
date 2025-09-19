import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try (TarExtractor extractor = new TarExtractor(tarFilePath, destDirectory)) {
            extractor.extract();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private final String tarFilePath;
    private final String destDirectory;

    public TarExtractor(String tarFilePath, String destDirectory) throws IOException {
        this.tarFilePath = tarFilePath;
        this.destDirectory = destDirectory;
        Files.createDirectories(Paths.get(destDirectory));
    }

    public void extract() throws IOException {
        try (InputStream fis = new FileInputStream(tarFilePath);
             InputStream is = tarFilePath.endsWith(".gz") ? new GZIPInputStream(fis) : fis;
             TarArchiveInputStream tais = new TarArchiveInputStream(is)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path filePath = Paths.get(destDirectory, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    try (BufferedOutputStream fos = new BufferedOutputStream(new FileOutputStream(filePath.toFile()))) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tais.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }

    @Override
    public void close() throws IOException {
        // No resources to close explicitly in this example
    }
}
