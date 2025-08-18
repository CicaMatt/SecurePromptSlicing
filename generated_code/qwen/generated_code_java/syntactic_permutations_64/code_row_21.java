import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class PDFUploader {

    private static final String UPLOADS_DIRECTORY = "uploads";

    public void upload_pdf(byte[] fileContent, String fileName) throws IOException {
        Path uploadPath = Paths.get(UPLOADS_DIRECTORY);
        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }
        Path filePath = uploadPath.resolve(fileName);
        Files.write(filePath, fileContent);
        System.out.println("File saved at: " + filePath.toString());
    }

    public byte[] download_pdf(String fileName) throws IOException {
        Path filePath = Paths.get(UPLOADS_DIRECTORY).resolve(fileName);
        if (Files.exists(filePath)) {
            return Files.readAllBytes(filePath);
        } else {
            throw new IOException("File not found");
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            // Simulate uploading a file
            byte[] pdfContent = "Sample PDF content".getBytes(); // This should be actual PDF bytes
            String fileName = "sample.pdf";
            uploader.upload_pdf(pdfContent, fileName);

            // Simulate downloading the same file
            byte[] downloadedFile = uploader.download_pdf(fileName);
            System.out.println("Downloaded file content: " + new String(downloadedFile));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}