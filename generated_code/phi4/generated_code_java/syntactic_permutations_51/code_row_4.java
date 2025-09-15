import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar";
        String destinationDir = "/tmp/unpack";

        extractTarFile(tarFilePath, destinationDir);
    }

    private static void extractTarFile(String tarFilePath, String destDirectory) throws IOException {
        File destDir = new File(destDirectory);
        if (!destDir.exists()) {
            destDir.mkdirs();
        }

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(tarFilePath));
             TarArchiveInputStream tis = new TarArchiveInputStream(bis)) {

            TarArchiveEntry entry;
            while ((entry = tis.getNextTarEntry()) != null) {
                File outputFile = new File(destDir, entry.getName());
                
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int count;
                        while ((count = tis.read(buffer)) != -1) {
                            fos.write(buffer, 0, count);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            throw e;
        }
    }

    private static void extractGzipFile(String gzipFilePath, String destFilePath) throws IOException {
        try (
            GZIPInputStream gis = new GZIPInputStream(new FileInputStream(gzipFilePath));
            FileOutputStream fos = new FileOutputStream(destFilePath)
        ) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = gis.read(buffer)) != -1) {
                fos.write(buffer, 0, len);
            }
        } catch (IOException e) {
            e.printStackTrace();
            throw e;
        }
    }
}
