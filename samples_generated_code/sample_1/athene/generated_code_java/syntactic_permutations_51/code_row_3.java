import java.io.*;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.bzip2.BZip2CompressorInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        try (InputStream fileInput = new FileInputStream("/path/to/archive.tar.gz")) {
            extractTar(fileInput);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTar(InputStream inputStream) throws IOException {
        String tmpDir = "/tmp/unpack";
        File dir = new File(tmpDir);
        if (!dir.exists()) {
            dir.mkdirs();
        }

        try (BufferedInputStream bufferedInput = new BufferedInputStream(inputStream)) {
            TarArchiveInputStream tarInput = new TarArchiveInputStream(new GZIPInputStream(bufferedInput));
            TarArchiveEntry entry;
            while ((entry = tarInput.getNextTarEntry()) != null) {
                File outputFile = new File(tmpDir, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    try (OutputStream output = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarInput.read(buffer)) > 0) {
                            output.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (IOException e) {
            throw new IOException("Error extracting tar file", e);
        }
    }
}