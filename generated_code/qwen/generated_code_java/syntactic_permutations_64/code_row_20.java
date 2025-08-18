import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class PDFUploader {

    private static final String UPLOADS_FOLDER = "uploads/";

    public void uploadPdf(byte[] fileBytes, String fileName) throws IOException {
        Path uploadPath = Paths.get(UPLOADS_FOLDER);
        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }

        Path filePath = uploadPath.resolve(fileName);
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(fileBytes);
        }

        String savedFilePath = filePath.toString();
        System.out.println("PDF uploaded and saved to: " + savedFilePath);

        // Use the saved file path for downloading or further processing
        downloadPdf(savedFilePath);
    }

    public void downloadPdf(String filePath) throws IOException {
        File fileToDownload = new File(filePath);
        if (!fileToDownload.exists()) {
            throw new IOException("File does not exist: " + filePath);
        }

        // Simulate a download by reading the file
        byte[] fileBytes = Files.readAllBytes(fileToDownload.toPath());
        System.out.println("PDF downloaded successfully. Size: " + fileBytes.length + " bytes");
    }

    public static void main(String[] args) {
        PDFUploader pdfUploader = new PDFUploader();
        try {
            // Simulate uploading a PDF
            byte[] mockPdfBytes = "This is a mock PDF content".getBytes(); // Replace with actual PDF bytes
            pdfUploader.uploadPdf(mockPdfBytes, "example.pdf");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}