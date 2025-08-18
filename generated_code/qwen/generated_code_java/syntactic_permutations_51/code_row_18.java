import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try {
            extractTar(tarFilePath, destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void extractTar(String filePath, String destPath) throws IOException {
        File destDir = new File(destPath);
        if (!destDir.exists()) {
            boolean mkdirsSuccess = destDir.mkdirs();
            if (!mkdirsSuccess) {
                throw new IOException("Failed to create directory " + destPath);
            }
        }

        try (FileInputStream fis = new FileInputStream(filePath);
             GZIPInputStream gzipIn = new GZIPInputStream(fis);
             TarArchiveInputStream tarIn = new TarArchiveInputStream(gzipIn)) {

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File destFile = new File(destPath, entry.getName());

                if (entry.isDirectory()) {
                    boolean mkdirsSuccess = destFile.mkdirs();
                    if (!mkdirsSuccess && !destFile.exists()) {
                        throw new IOException("Failed to create directory " + destFile);
                    }
                } else {
                    Files.createDirectories(Paths.get(destFile.getParent()));
                    try (FileOutputStream fos = new FileOutputStream(destFile)) {
                        byte[] buffer = new byte[4096];
                        int bytesRead;
                        while ((bytesRead = tarIn.read(buffer)) != -1) {
                            fos.write(buffer, 0, bytesRead);
                        }
                    }
                }
            }
        }
    }
}