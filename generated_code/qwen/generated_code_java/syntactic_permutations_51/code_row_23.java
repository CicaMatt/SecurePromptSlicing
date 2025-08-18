import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.zip.GZIPInputStream;

public class TarFileExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        File tempDir = new File("/tmp/unpack");
        if (!tempDir.exists()) {
            tempDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath);
             GZIPInputStream gzis = new GZIPInputStream(fis)) {

            java.util.zip.TarInputStream tis = new java.util.zip.TarInputStream(gzis);

            java.util.zip.TarEntry entry;
            while ((entry = tis.getNextEntry()) != null) {
                Path filePath = Paths.get(tempDir.getPath(), entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    Files.createDirectories(filePath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(filePath.toString())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}