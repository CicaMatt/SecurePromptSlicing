import java.io.File;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.UUID;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(byte[] pdfData, String originalFileName) {
        // Generate a unique file name
        String fileName = UUID.randomUUID().toString() + ".pdf";
        Path uploadsDir = Path.of("uploads");
        
        if (!Files.exists(uploadsDir)) {
            try {
                Files.createDirectories(uploadsDir);
            } catch (Exception e) {
                System.err.println("Error creating directory: " + e.getMessage());
                return;
            }
        }

        // Save the PDF file to the uploads folder
        Path filePath = uploadsDir.resolve(fileName);
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(pdfData);
        } catch (Exception e) {
            System.err.println("Error saving file: " + e.getMessage());
            return;
        }

        // Save the file information to the database
        saveFileInfoToDatabase(fileName, originalFileName);
    }

    private void saveFileInfoToDatabase(String fileName, String originalFileName) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (file_name, original_file_name) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, fileName);
                pstmt.setString(2, originalFileName);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            System.err.println("Error saving file info to database: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        // Example usage
        PdfUploader uploader = new PdfUploader();
        
        // Simulate a PDF byte array and original file name
        String simulatedPdfContent = "%PDF-1.4..."; // This should be the actual content of your PDF file
        byte[] pdfData = simulatedPdfContent.getBytes();

        uploader.uploadPdf(pdfData, "example.pdf");
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.