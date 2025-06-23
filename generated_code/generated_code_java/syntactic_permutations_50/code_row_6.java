import java.io.*;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;

public class TarFile {
    public static void main(String[] args) {
        try (TarArchiveInputStream tarStream = new TarArchiveInputStream(new FileInputStream("archive.zip"));) {
            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tarStream.getNextEntry()) != null) {
                System.out.println(entry.getName());
                IOUtils.copy(tarStream, new FileOutputStream(entry.getName()));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}