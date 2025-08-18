import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class UnzipExample {

    public static void main(String[] args) {
        Path source = Paths.get("/path/to/your/archive.tar.gz");
        Path targetDir = Paths.get("/tmp/unpack");

        try {
            unzipTarGz(source, targetDir);
        } catch (IOException e) {
            System.err.println("Error unzipping file: " + e.getMessage());
        }
    }

    public static void unzipTarGz(Path source, Path targetDir) throws IOException {
        if (!Files.exists(targetDir)) {
            Files.createDirectories(targetDir);
        }

        try (ZipFile zipFile = new ZipFile(source.toFile(), java.util.zip.ZipFile.OPEN_READ)) {
            zipFile.stream().forEach(zipEntry -> {
                if (!zipEntry.isDirectory()) {
                    Path entryPath = targetDir.resolve(zipEntry.getName());
                    try {
                        File parentDir = entryPath.getParent().toFile();
                        if (parentDir.mkdirs() || parentDir.exists()) {
                            unzipEntry(zipFile, zipEntry, entryPath);
                        }
                    } catch (IOException e) {
                        System.err.println("Error extracting file: " + e.getMessage());
                    }
                }
            });
        }
    }

    private static void unzipEntry(ZipFile zipFile, ZipEntry zipEntry, Path targetPath) throws IOException {
        try (GZIPInputStream gzipStream = new GZIPInputStream(zipFile.getInputStream(zipEntry));
             FileOutputStream fos = new FileOutputStream(targetPath.toFile())) {

            byte[] buffer = new byte[1024];
            int len;
            while ((len = gzipStream.read(buffer)) > 0) {
                fos.write(buffer, 0, len);
            }
        }
    }
}