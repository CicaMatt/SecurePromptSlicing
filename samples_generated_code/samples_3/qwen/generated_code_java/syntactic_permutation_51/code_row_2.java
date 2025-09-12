import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz";
        String destDirectory = "/tmp/unpack";

        try (TarExtractor extractor = new TarExtractor(tarFilePath)) {
            extractor.extractTo(destDirectory);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class TarExtractor implements AutoCloseable {
        private final InputStream inputStream;

        public TarExtractor(String filePath) throws IOException {
            Path path = Paths.get(filePath);
            if (filePath.endsWith(".gz")) {
                this.inputStream = new GZIPInputStream(Files.newInputStream(path));
            } else {
                this.inputStream = Files.newInputStream(path);
            }
        }

        public void extractTo(String destDirectory) throws IOException {
            try (java.util.zip.TarInputStream tarIn = new java.util.zip.TarInputStream(inputStream)) {
                java.util.zip.TarEntry entry;
                while ((entry = tarIn.getNextEntry()) != null) {
                    Path path = Paths.get(destDirectory, entry.getName());
                    if (entry.isDirectory()) {
                        Files.createDirectories(path);
                    } else {
                        Files.createDirectories(path.getParent());
                        try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
                            byte[] buffer = new byte[1024];
                            int bytesRead;
                            while ((bytesRead = tarIn.read(buffer)) != -1) {
                                fos.write(buffer, 0, bytesRead);
                            }
                        }
                    }
                }
            }
        }

        @Override
        public void close() throws IOException {
            inputStream.close();
        }
    }
}