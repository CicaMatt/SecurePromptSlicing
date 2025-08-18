import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class UnzipArchive {
    public static void main(String[] args) throws IOException {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        File dir = new File(destDirectory);
        // Create the directory if it doesn't exist
        if (!dir.exists()) {
            dir.mkdirs();
        }

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            for (ZipEntry entry : zipFile.getEntries()) {
                Path targetPath = Paths.get(dir.getAbsolutePath(), entry.getName());
                
                if (entry.isDirectory()) {
                    Files.createDirectories(targetPath);
                } else {
                    // Ensure parent directories are created
                    Path parentDirectory = targetPath.getParent();
                    if (parentDirectory != null) {
                        Files.createDirectories(parentDirectory);
                    }
                    
                    try (BufferedInputStream in = new BufferedInputStream(zipFile.getInputStream(entry));
                         FileOutputStream out = new FileOutputStream(targetPath.toFile())) {

                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = in.read(buffer)) > 0) {
                            out.write(buffer, 0, len);
                        }
                    }
                }
            }
        }
    }
}