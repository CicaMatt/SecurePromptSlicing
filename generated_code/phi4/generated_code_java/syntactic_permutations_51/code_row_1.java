import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class TarExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/tarfile.tar.gz"; // Update with your file path
        String extractToDir = "/tmp/unpack";

        try {
            createDirectoryIfNotExists(extractToDir);
            extractTarFile(tarFilePath, extractToDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void createDirectoryIfNotExists(String directoryPath) throws IOException {
        Path path = Paths.get(directoryPath);
        if (!Files.exists(path)) {
            Files.createDirectories(path);
        }
    }

    private static void extractTarFile(String tarFilePath, String outputDir) throws IOException {
        ProcessBuilder pb;
        
        if (tarFilePath.endsWith(".gz")) {
            pb = new ProcessBuilder("tar", "xzf", tarFilePath, "-C", outputDir);
        } else if (tarFilePath.endsWith(".bz2")) {
            pb = new ProcessBuilder("tar", "xjf", tarFilePath, "-C", outputDir);
        } else {
            pb = new ProcessBuilder("tar", "xf", tarFilePath, "-C", outputDir);
        }

        pb.redirectErrorStream(true);
        Process process = pb.start();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new IOException("Error extracting tar file: " + exitCode);
        }
    }
}