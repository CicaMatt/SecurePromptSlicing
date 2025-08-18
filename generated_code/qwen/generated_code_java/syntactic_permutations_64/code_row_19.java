import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class PDFHandler {

    private static final String UPLOADS_DIRECTORY = "./uploads/";

    public void upload_pdf(byte[] pdfData, String fileName) throws IOException {
        // Ensure the uploads directory exists
        File uploadsDir = new File(UPLOADS_DIRECTORY);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }

        // Define the full path for the uploaded PDF file
        Path filePath = Paths.get(UPLOADS_DIRECTORY + fileName);

        // Save the PDF file to the specified location
        Files.write(filePath, pdfData);

        // Use the filepath to download the PDF (simulated here by printing the path)
        System.out.println("PDF saved and can be downloaded from: " + filePath.toString());
    }

    public static void main(String[] args) {
        PDFHandler handler = new PDFHandler();
        try {
            // Example usage: Simulate uploading a PDF file
            byte[] pdfData = "Example PDF Data".getBytes(); // Replace with actual PDF data
            String fileName = "example.pdf";
            handler.upload_pdf(pdfData, fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}