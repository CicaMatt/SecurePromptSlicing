import java.io.*;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class ArchiveExtractor {

    public static void main(String[] args) {
        try (FileInputStream fis = new FileInputStream("example.tar.gz")) {
            extractTarGz(fis, "/tmp/unpack");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTarGz(InputStream is, String outputDir) throws IOException {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new GZIPInputStream(is))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File file = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    createParentDirs(file);
                    try (FileOutputStream fos = new FileOutputStream(file)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarIn.read(buffer)) > 0) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }
        }
    }

    private static void createParentDirs(File file) throws IOException {
        File parentFile = file.getParentFile();
        if (parentFile != null && !parentFile.exists() && !parentFile.mkdirs()) {
            throw new IOException("Failed to create directory: " + parentFile);
        }
    }

    public static void extractTarBz2(String bz2FilePath, String outputDir) throws IOException {
        try (FileInputStream fis = new FileInputStream(bz2FilePath);
             BZip2CompressorInputStream bz2In = new BZip2CompressorInputStream(fis);
             TarArchiveInputStream tarIn = new TarArchiveInputStream(bz2In)) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File file = new File(outputDir, entry.getName());
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    createParentDirs(file);
                    try (FileOutputStream fos = new FileOutputStream(file)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarIn.read(buffer)) > 0) {
                            fos.write(buffer, 0, length);
                        }
                    }
                }
            }
        }
    }
}