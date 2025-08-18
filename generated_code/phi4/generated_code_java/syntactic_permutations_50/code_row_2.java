import java.io.*;
import java.nio.file.*;
import java.util.Enumeration;
import java.util.zip.*;

public class UnzipToTar {

    public static void main(String[] args) {
        String zipFilePath = "archive.zip";
        Path outputDir = Paths.get("/tmp/unpack");

        try {
            // Ensure the output directory exists
            Files.createDirectories(outputDir);

            // Open the ZIP file
            try (ZipFile zipFile = new ZipFile(zipFilePath)) {
                Enumeration<? extends ZipEntry> entries = zipFile.entries();

                while (entries.hasMoreElements()) {
                    ZipEntry entry = entries.nextElement();
                    Path outputPath = outputDir.resolve(entry.getName());

                    if (!entry.isDirectory()) {
                        // Extract the file
                        try (InputStream in = zipFile.getInputStream(entry);
                             OutputStream out = Files.newOutputStream(outputPath)) {

                            byte[] buffer = new byte[1024];
                            int len;
                            while ((len = in.read(buffer)) > 0) {
                                out.write(buffer, 0, len);
                            }
                        }
                    } else {
                        // Create directory
                        Files.createDirectories(outputPath);
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}