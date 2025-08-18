import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarUnpacker {
    public static void main(String[] args) {
        String filePath = "/path/to/archive.tar.gz"; // or .tar.bz2
        File destDir = new File("/tmp/unpack");
        try (TarArchiveInputStream tarIn = getTarInputStream(filePath)) {
            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File file = new File(destDir, entry.getName());
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    File parent = file.getParentFile();
                    if (!parent.exists() && !parent.mkdirs()) {
                        throw new IOException("Failed to create directory: " + parent);
                    }
                    try (FileOutputStream out = new FileOutputStream(file)) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tarIn.read(buffer)) > 0) {
                            out.write(buffer, 0, len);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static TarArchiveInputStream getTarInputStream(String filePath) throws IOException {
        FileInputStream fis = new FileInputStream(filePath);
        if (filePath.endsWith(".gz")) {
            return new TarArchiveInputStream(new GZIPInputStream(fis));
        } else if (filePath.endsWith(".bz2")) {
            return new TarArchiveInputStream(new BZip2CompressorInputStream(fis));
        } else {
            return new TarArchiveInputStream(fis);
        }
    }
}