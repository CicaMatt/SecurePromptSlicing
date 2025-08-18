import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class ExtractZipToTar {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String extractDirPath = "/tmp/unpack";

        File destDir = new File(extractDirPath);
        if (!destDir.exists()) {
            Files.createDirectories(Paths.get(extractDirPath));
        }

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            zipFile.stream()
                   .forEach(entry -> {
                       try {
                           Path entryDestination = Paths.get(destDir.getAbsolutePath(), entry.getName());
                           if (!entry.isDirectory()) {
                               byte[] buffer = new byte[1024];
                               try (BufferedInputStream bis = new BufferedInputStream(zipFile.getInputStream(entry));
                                    FileOutputStream fos = new FileOutputStream(entryDestination.toFile())) {
                                   int read;
                                   while ((read = bis.read(buffer)) != -1) {
                                       fos.write(buffer, 0, read);
                                   }
                               }
                           } else {
                               Files.createDirectories(entryDestination);
                           }
                       } catch (Exception e) {
                           e.printStackTrace();
                       }
                   });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}