import java.util.*;
import java.lang.String;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.apache.commons.compress.archivers.ArchiveException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;
import java.util.zip.*;

class TarFile {
public static void main(String[] args) {
    String filePath = "/path/to/file.tar"; // path to tar file
    String destDir = "/tmp/unpack/"; // destination directory to extract into
    try (TarArchiveInputStream tais = new TarArchiveInputStream(new FileInputStream(filePath))) {
        TarArchiveEntry entry;
        while ((entry = tais.getNextTarEntry()) != null) {
            System.out.println("Unpacking file: " + entry.getName());
            if (entry.isDirectory()) {
                Files.createDirectories(Paths.get(destDir, entry.getName()));
            } else {
                try (OutputStream os = Files.newOutputStream(Paths.get(destDir, entry.getName()))) {
                    IOUtils.copy(tais, os);
                }
            }
        }
    } catch (IOException | ArchiveException e) {
        System.out.println("Error occurred while unpacking tar file: " + e.getMessage());
    }
}
}