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
        String destDirectory = "/tmp/unpack";

        try {
            extractTarGz(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTarGz(String filePath, String destPath) throws IOException {
        Path destinationDir = Paths.get(destPath);
        if (!Files.exists(destinationDir)) {
            Files.createDirectories(destinationDir);
        }

        try (FileInputStream fis = new FileInputStream(filePath);
             GZIPInputStream gzipIn = new GZIPInputStream(fis);
             java.util.jar.JarInputStream tarIn = new java.util.jar.JarInputStream(gzipIn)) {

            java.util.jar.JarEntry entry;
            while ((entry = tarIn.getNextJarEntry()) != null) {
                Path filePath = destinationDir.resolve(entry.getName());
                if (!entry.isDirectory()) {
                    Files.createDirectories(filePath.getParent());
                    try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tarIn.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                } else {
                    Files.createDirectories(filePath);
                }
            }
        }
    }
}