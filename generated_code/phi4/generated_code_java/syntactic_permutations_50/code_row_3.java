import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class UnzipArchive {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        String destDirectory = "/tmp/unpack";

        File directory = new File(destDirectory);
        if (!directory.exists()) {
            directory.mkdirs();
        }

        try (ZipInputStream zis = new ZipInputStream(new BufferedInputStream(new FileInputStream(zipFilePath)))) {
            ZipEntry zipEntry = zis.getNextEntry();

            while (zipEntry != null) {
                Path filePath = Paths.get(destDirectory + File.separator + zipEntry.getName());
                if (!filePath.startsWith(Paths.get(destDirectory))) {
                    throw new IOException("Entry is outside of the target directory: " + zipEntry.getName());
                }
                
                if (zipEntry.isDirectory()) {
                    Files.createDirectories(filePath);
                } else {
                    parentDirsExist(filePath);
                    
                    try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = zis.read(buffer)) > 0) {
                            fos.write(buffer, 0, len);
                        }
                    }
                }

                zipEntry = zis.getNextEntry();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void parentDirsExist(Path path) throws IOException {
        Path parent = path.getParent();
        if (parent != null && !Files.exists(parent)) {
            parentDirsExist(parent);
            Files.createDirectory(parent);
        }
    }
}