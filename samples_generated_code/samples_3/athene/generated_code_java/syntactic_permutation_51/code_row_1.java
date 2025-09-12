import java.io.*;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarUnpacker {
    public static void main(String[] args) {
        try (InputStream fileStream = new FileInputStream("/path/to/archive.tar.gz")) {
            try (InputStream gzipStream = new GZIPInputStream(fileStream)) {
                unpackTarArchive(gzipStream, "/tmp/unpack");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (InputStream fileStream = new FileInputStream("/path/to/archive.tar.bz2")) {
            try (InputStream bzip2Stream = new BZip2CompressorInputStream(fileStream)) {
                unpackTarArchive(bzip2Stream, "/tmp/unpack");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void unpackTarArchive(InputStream stream, String destinationDir) throws IOException {
        try (TarArchiveInputStream tarInput = new TarArchiveInputStream(stream)) {
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File destFile = new File(destinationDir, entry.getName());
                if (entry.isDirectory()) {
                    destFile.mkdirs();
                } else {
                    try (OutputStream out = new FileOutputStream(destFile)) {
                        IOUtils.copy(tarInput, out);
                    }
                }
            }
        }
    }
}