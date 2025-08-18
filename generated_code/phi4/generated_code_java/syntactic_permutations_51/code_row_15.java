import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class TarFileUnpacker {
    public static void main(String[] args) {
        String tarFilePath = "your_tar_file.tar"; // Replace with your actual tar file path
        String extractDirPath = "/tmp/unpack";

        try {
            File directory = new File(extractDirPath);
            if (!directory.exists()) {
                Files.createDirectories(Paths.get(extractDirPath));
            }

            ProcessBuilder processBuilder = new ProcessBuilder("tar", "-xf", tarFilePath, "-C", extractDirPath);
            Process process = processBuilder.start();

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Extraction completed successfully.");
            } else {
                System.err.println("Error during extraction. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}