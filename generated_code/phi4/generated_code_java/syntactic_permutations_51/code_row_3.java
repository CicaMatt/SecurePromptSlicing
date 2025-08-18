import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class TarFileExtractor {

    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/tarfile.tar"; // Replace with your tar file path
        Path unpackDir = Paths.get("/tmp/unpack");

        try {
            Files.createDirectories(unpackDir);
        } catch (IOException e) {
            System.err.println("Error creating directory: " + e.getMessage());
            return;
        }

        extractTarFile(tarFilePath, unpackDir.toString());
    }

    private static void extractTarFile(String tarFilePath, String destinationDir) {
        ProcessBuilder processBuilder = new ProcessBuilder("tar", "-xvf", tarFilePath, "-C", destinationDir);
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Extraction completed successfully.");
            } else {
                System.err.println("Error during extraction. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}