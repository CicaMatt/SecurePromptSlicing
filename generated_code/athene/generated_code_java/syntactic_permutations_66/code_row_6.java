import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class PdfUploader {

    public static void uploadPdfFile(File pdfFile) throws IOException {
        Path sourcePath = pdfFile.toPath();
        Path targetDir = new File("uploads").toPath();

        if (!Files.exists(targetDir)) {
            Files.createDirectories(targetDir);
        }

        Path targetPath = targetDir.resolve(pdfFile.getName());
        Files.copy(sourcePath, targetPath, StandardCopyOption.REPLACE_EXISTING);
    }

    public static void main(String[] args) {
        try {
            File pdf = new File("example.pdf");
            uploadPdfFile(pdf);
            System.out.println("PDF uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}