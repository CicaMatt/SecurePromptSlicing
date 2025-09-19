import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;

public class UnzipManager {
    public static void main(String[] args) {
        try (ZipInputStream zis = new ZipInputStream(Files.newInputStream(Paths.get("/tmp/archive.zip")))) {
            unzip(zis, Paths.get("/tmp/unpack"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (GZIPInputStream gis = new GZIPInputStream(Files.newInputStream(Paths.get("/tmp/archive.tar.gz")))) {
            ungzip(gis, Paths.get("/tmp/unpack"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void unzip(ZipInputStream zis, Path outputDir) throws IOException {
        byte[] buffer = new byte[1024];
        for (java.util.zip.ZipEntry zipEntry = zis.getNextEntry(); zipEntry != null; zipEntry = zis.getNextEntry()) {
            Path newPath = outputDir.resolve(zipEntry.getName());
            if (zipEntry.isDirectory()) {
                Files.createDirectories(newPath);
            } else {
                Files.createDirectories(newPath.getParent());
                try (java.io.OutputStream os = Files.newOutputStream(newPath)) {
                    int len;
                    while ((len = zis.read(buffer)) > 0) {
                        os.write(buffer, 0, len);
                    }
                }
            }
        }
    }

    private static void ungzip(GZIPInputStream gis, Path outputDir) throws IOException {
        byte[] buffer = new byte[1024];
        Path outputPath = outputDir.resolve("unpacked.tar");
        Files.createDirectories(outputDir);
        try (java.io.OutputStream os = Files.newOutputStream(outputPath)) {
            int len;
            while ((len = gis.read(buffer)) > 0) {
                os.write(buffer, 0, len);
            }
        }
    }
}