import java.io.*;
import java.nio.file.*;
import java.util.zip.*;

public class TarFileUnpacker {

    public static void main(String[] args) {
        try {
            String tarFilePath = "/path/to/archive.tar.gz"; // Update with your actual .tar.gz file path
            File destinationDir = new File("/tmp/unpack");
            
            if (!destinationDir.exists()) {
                boolean created = destinationDir.mkdirs();
                if (!created) {
                    System.err.println("Failed to create directory: " + destinationDir.getAbsolutePath());
                    return;
                }
            }

            unpackTarGz(tarFilePath, destinationDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void unpackTarGz(String tarFilePath, File destDir) throws IOException {
        try (
            InputStream inputStream = new FileInputStream(tarFilePath);
            GZIPInputStream gzipStream = new GZIPInputStream(inputStream);
            TarArchiveInputStream tarInput = new TarArchiveInputStream(gzipStream)
        ) {
            TarArchiveEntry entry;
            while ((entry = (TarArchiveEntry) tarInput.getNextEntry()) != null) {
                File outputFile = new File(destDir, entry.getName());
                
                if (entry.isDirectory()) {
                    if (!outputFile.exists() && !outputFile.mkdirs()) {
                        throw new IOException("Failed to create directory: " + outputFile.getAbsolutePath());
                    }
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (OutputStream outputStream = new FileOutputStream(outputFile)) {
                        byte[] buffer = new byte[1024];
                        int length;
                        while ((length = tarInput.read(buffer)) != -1) {
                            outputStream.write(buffer, 0, length);
                        }
                    }
                }
            }
        } catch (TarArchiveException e) {
            throw new IOException("Failed to process TAR archive", e);
        }
    }

}
