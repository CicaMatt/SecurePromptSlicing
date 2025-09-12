import java.io.*;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class ArchiveExtractor {

    public static void extractTarGz(String tarGzFilePath) throws IOException {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new GZIPInputStream(new FileInputStream(tarGzFilePath)))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File file = new File("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    createParentDirectories(file);
                    try (OutputStream out = new FileOutputStream(file)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarIn.read(buffer)) != -1) {
                            out.write(buffer, 0, length);
                        }
                    }
                }
            }
        }
    }

    public static void extractTarBz2(String tarBz2FilePath) throws IOException {
        try (TarArchiveInputStream tarIn = new TarArchiveInputStream(new BZip2CompressorInputStream(new FileInputStream(tarBz2FilePath)))) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File file = new File("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    createParentDirectories(file);
                    try (OutputStream out = new FileOutputStream(file)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarIn.read(buffer)) != -1) {
                            out.write(buffer, 0, length);
                        }
                    }
                }
            }
        }
    }

    private static void createParentDirectories(File file) throws IOException {
        File parentFile = file.getParentFile();
        if (parentFile != null && !parentFile.exists()) {
            if (!parentFile.mkdirs()) {
                throw new IOException("Failed to create directory: " + parentFile);
            }
        }
    }

    public static void main(String[] args) {
        try {
            extractTarGz("/path/to/your/tar.gz");
            extractTarBz2("/path/to/your/tar.bz2");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}