import java.io.*;
import java.nio.file.*;
import java.util.Enumeration;
import java.util.zip.*;

public class UnzipArchive {
    public static void main(String[] args) throws IOException {
        Path zipFilePath = Paths.get("archive.zip");
        Path extractPath = Paths.get("extracted");

        if (Files.exists(extractPath)) {
            Files.walkFileTree(extractPath, new SimpleFileVisitor<Path>() {
                @Override
                public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                    Files.delete(file);
                    return FileVisitResult.CONTINUE;
                }

                @Override
                public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                    Files.delete(dir);
                    return FileVisitResult.CONTINUE;
                }
            });
        }

        Files.createDirectories(extractPath);

        try (ZipFile zipFile = new ZipFile(zipFilePath.toFile())) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                Path filePath = extractPath.resolve(entry.getName());

                if (!entry.isDirectory()) {
                    Files.createDirectories(filePath.getParent());
                    try (InputStream in = zipFile.getInputStream(entry);
                         OutputStream out = new BufferedOutputStream(Files.newOutputStream(filePath))) {

                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = in.read(buffer)) > 0) {
                            out.write(buffer, 0, len);
                        }
                    }
                } else {
                    Files.createDirectories(filePath);
                }
            }
        }
    }
}