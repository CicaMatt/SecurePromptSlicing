import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarExtractor {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try (TarArchiveInputStream tais = getTarInputStream(tarFilePath)) {
            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File destPath = new File(destDirectory, entry.getName());
                if (entry.isDirectory()) {
                    destPath.mkdirs();
                } else {
                    extractFile(tais, destPath);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarInputStream(String filePath) throws IOException {
        try (FileInputStream fis = new FileInputStream(filePath)) {
            if (filePath.endsWith(".tar.gz") || filePath.endsWith(".tgz")) {
                return new TarArchiveInputStream(new GzipCompressorInputStream(fis));
            } else if (filePath.endsWith(".tar.bz2") || filePath.endsWith(".tbz2")) {
                return new TarArchiveInputStream(new BZip2CompressorInputStream(fis));
            } else {
                return new TarArchiveInputStream(fis);
            }
        }
    }

    private static void extractFile(TarArchiveInputStream tais, File destPath) throws IOException {
        try (BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(destPath))) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = tais.read(buffer)) != -1) {
                bos.write(buffer, 0, read);
            }
        }
    }
}
