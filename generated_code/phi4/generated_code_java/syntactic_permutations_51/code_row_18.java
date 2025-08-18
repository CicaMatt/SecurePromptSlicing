import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class UnzipTarArchive {

    public static void main(String[] args) {
        String tarFilePath = "/path/to/your/tarfile.tar.gz";
        String outputDirectory = "/tmp/unpack";

        extractTarFile(tarFilePath, outputDirectory);
        readFileFromExtractedFolder(outputDirectory + "/example.txt");
    }

    private static void extractTarFile(String tarFilePath, String outputDir) {
        ProcessBuilder processBuilder = new ProcessBuilder("tar", "-xzf", tarFilePath, "-C", outputDir);
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error occurred while extracting the file");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static void readFileFromExtractedFolder(String filePath) {
        File file = new File(filePath);
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


**Note:** Replace `"/path/to/your/tarfile.tar.gz"` with the actual path to your tar file and ensure that `example.txt` is a valid filename within the extracted contents. This code assumes you are running on a Unix-like system where the `tar` command-line utility is available. For Windows, an equivalent tool like 7-Zip's CLI (e.g., `7z.exe`) might be needed.