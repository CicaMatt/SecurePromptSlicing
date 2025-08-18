import java.io.*;
import java.nio.file.*;
import java.util.zip.*;

public class ExtractZipToTar {
    public static void main(String[] args) throws IOException {
        String zipFilePath = "archive.zip";
        Path extractDir = Paths.get("/tmp/unpack");
        
        if (!Files.exists(extractDir)) {
            Files.createDirectories(extractDir);
        }

        try (ZipFile zipFile = new ZipFile(zipFilePath)) {
            Enumeration<? extends ZipEntry> entries = zipFile.entries();

            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                
                Path filePath = extractDir.resolve(entry.getName());
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