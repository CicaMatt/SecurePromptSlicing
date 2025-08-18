import java.io.*;
import java.nio.file.*;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar";
        Path destDir = Paths.get("/tmp/unpack");

        try (TarArchiveInputStream in = getTarArchiveInputStream(tarFilePath)) {
            TarArchiveEntry entry;
            while ((entry = in.getNextTarEntry()) != null) {
                Path path = destDir.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(path);
                } else {
                    Files.createDirectories(path.getParent());
                    try (OutputStream out = new FileOutputStream(path.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = in.read(buffer)) > 0) {
                            out.write(buffer, 0, len);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarArchiveInputStream(String filePath) throws IOException {
        InputStream fileStream = new FileInputStream(filePath);
        if (filePath.endsWith(".tar.gz") || filePath.endsWith(".tgz")) {
            return new TarArchiveInputStream(new GzipCompressorInputStream(fileStream));
        } else if (filePath.endsWith(".tar.bz2") || filePath.endsWith(".tbz2")) {
            return new TarArchiveInputStream(new BZip2CompressorInputStream(fileStream));
        } else if (filePath.endsWith(".tar")) {
            return new TarArchiveInputStream(fileStream);
        } else {
            throw new IllegalArgumentException("Unsupported file format");
        }
    }
}