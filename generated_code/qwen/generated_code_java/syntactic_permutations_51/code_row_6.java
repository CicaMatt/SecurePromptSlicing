import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirPath = "/tmp/unpack";

        try {
            extractTarGz(tarFilePath, destDirPath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void extractTarGz(String filePath, String destDirPath) throws IOException {
        Path destDir = Paths.get(destDirPath);
        if (!Files.exists(destDir)) {
            Files.createDirectories(destDir);
        }

        try (FileInputStream fis = new FileInputStream(filePath);
             GZIPInputStream gis = new GZIPInputStream(fis);
             java.util.zip.TarInputStream tis = new java.util.zip.TarInputStream(gis)) {

            java.util.zip.TarEntry entry;
            while ((entry = tis.getNextEntry()) != null) {
                Path destPath = destDir.resolve(entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(destPath);
                } else {
                    Files.createDirectories(destPath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(destPath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }
}