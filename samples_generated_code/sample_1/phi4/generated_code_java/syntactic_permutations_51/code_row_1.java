import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

public class TarFileExtractor {
    public static void main(String[] args) {
        String source = "example.tar.gz"; // Replace with your tar file path
        String destinationDir = "/tmp/unpack";
        
        try {
            extractTarfile(source, destinationDir);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static void extractTarfile(String source, String dest) throws IOException {
        File file = new File(source);
        if (!file.exists()) {
            throw new IOException("Source file does not exist");
        }
        
        ProcessBuilder pb = new ProcessBuilder("tar", "xzf", source, "-C", dest);
        Process process = pb.start();
        
        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new IOException("Failed to extract tar file: Exit code " + exitCode);
        }
    }

    public static void writeFile(String path, String content) throws IOException {
        File file = new File(path);
        Files.write(file.toPath(), content.getBytes());
    }

    public static void readFile(String path) throws IOException {
        byte[] data = Files.readAllBytes(new File(path).toPath());
        System.out.println(new String(data));
    }
}


Make sure you have the necessary permissions to read/write files in the specified directories and that `tar` is available on your system. You may need to adjust paths or commands based on your environment.