import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;
import java.util.zip.BZip2InputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarFileUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz"; // or .tar.bz2
        String outputDirPath = "/tmp/unpack";

        File outputDir = new File(outputDirPath);
        if (!outputDir.exists()) {
            outputDir.mkdirs();
        }

        try (FileInputStream fis = new FileInputStream(tarFilePath)) {
            TarArchiveInputStream tais;
            if (tarFilePath.endsWith(".gz")) {
                tais = new TarArchiveInputStream(new GZIPInputStream(fis));
            } else if (tarFilePath.endsWith(".bz2")) {
                tais = new TarArchiveInputStream(new BZip2InputStream(fis));
            } else {
                tais = new TarArchiveInputStream(fis);
            }

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                Path entryPath = Paths.get(outputDirPath, entry.getName());
                if (entry.isDirectory()) {
                    Files.createDirectories(entryPath);
                } else {
                    File parentFile = entryPath.getParent().toFile();
                    if (!parentFile.exists()) {
                        parentFile.mkdirs();
                    }
                    try (FileOutputStream fos = new FileOutputStream(entryPath.toFile())) {
                        IOUtils.copy(tais, fos);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}