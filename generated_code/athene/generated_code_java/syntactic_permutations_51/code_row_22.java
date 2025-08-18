import java.io.*;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarUnpacker {
    public static void main(String[] args) throws IOException {
        try (FileInputStream fis = new FileInputStream("/path/to/archive.tar.gz");
             BufferedInputStream bis = new BufferedInputStream(fis);
             InputStream is = "gz".equals(getCompressionType("/path/to/archive.tar.gz")) ?
                 new GZIPInputStream(bis) : 
                 "bz2".equals(getCompressionType("/path/to/archive.tar.gz")) ? 
                     new BZip2CompressorInputStream(bis) :
                     bis;
             TarArchiveInputStream tais = new TarArchiveInputStream(is)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                File file = new File("/tmp/unpack", entry.getName());
                if (entry.isDirectory()) {
                    file.mkdirs();
                } else {
                    File parent = file.getParentFile();
                    if (!parent.exists()) {
                        parent.mkdirs();
                    }
                    try (OutputStream out = new FileOutputStream(file)) {
                        IOUtils.copy(tais, out);
                    }
                }
            }
        }
    }

    private static String getCompressionType(String fileName) {
        if (fileName.endsWith(".tar.gz") || fileName.endsWith(".tgz")) {
            return "gz";
        } else if (fileName.endsWith(".tar.bz2")) {
            return "bz2";
        }
        return "";
    }
}