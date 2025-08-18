import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipInputStream;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarExtractor {

    public static void extractTarGz(String tarGzFilePath, String destDir) {
        try (FileInputStream fis = new FileInputStream(tarGzFilePath);
             GZIPInputStream gis = new GZIPInputStream(fis);
             TarArchiveInputStream tais = new TarArchiveInputStream(gis)) {

            TarArchiveEntry entry;
            while ((entry = tais.getNextTarEntry()) != null) {
                String entryName = destDir + java.io.File.separator + entry.getName();
                if (entry.isDirectory()) {
                    new java.io.File(entryName).mkdirs();
                } else {
                    try (FileOutputStream fos = new FileOutputStream(entryName)) {
                        IOUtils.copy(tais, fos);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        extractTarGz("path/to/archive.tar.gz", "path/to/destination");
    }
}