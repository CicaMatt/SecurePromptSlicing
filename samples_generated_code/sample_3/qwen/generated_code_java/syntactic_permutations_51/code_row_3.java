import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "example.tar.gz";
        Path destinationDir = Paths.get("/tmp/unpack");

        try {
            Files.createDirectories(destinationDir);
            if (tarFilePath.endsWith(".gz")) {
                try (GZIPInputStream gzipIn = new GZIPInputStream(new FileInputStream(tarFilePath));
                     TarArchiveInputStream tarIn = new TarArchiveInputStream(gzipIn)) {
                    extractTar(tarIn, destinationDir);
                }
            } else {
                try (FileInputStream fis = new FileInputStream(tarFilePath);
                     TarArchiveInputStream tarIn = new TarArchiveInputStream(fis)) {
                    extractTar(tarIn, destinationDir);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTar(TarArchiveInputStream tarIn, Path destinationDir) throws IOException {
        TarArchiveEntry entry;
        while ((entry = tarIn.getNextTarEntry()) != null) {
            File destPath = new File(destinationDir.toFile(), entry.getName());
            if (entry.isDirectory()) {
                Files.createDirectories(destPath.toPath());
            } else {
                extractFile(tarIn, destPath);
            }
        }
    }

    private static void extractFile(TarArchiveInputStream tarIn, File destPath) throws IOException {
        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(destPath))) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = tarIn.read(buffer)) != -1) {
                bos.write(buffer, 0, read);
            }
        }
    }
}
