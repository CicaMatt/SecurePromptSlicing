import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "path/to/your/archive.tar.gz"; // Replace with your tar file path
        String extractionPath = "/tmp/unpack";

        extractTarGz(tarFilePath, extractionPath);
    }

    private static void extractTarGz(String tarFilePath, String extractionDir) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            processBuilder.command("tar.exe", "-xzf", tarFilePath, "-C", extractionDir);
        } else {
            processBuilder.command("tar", "xzvf", tarFilePath, "-C", extractionDir);
        }

        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                System.out.println("Extraction completed successfully.");
            } else {
                System.err.println("Extraction failed with error code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
