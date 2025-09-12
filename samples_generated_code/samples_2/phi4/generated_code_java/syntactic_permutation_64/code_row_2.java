import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void uploadPdf(String pdfFilePath, String filename) {
        try {
            Path destPath = Files.createTempFile("upload-", ".pdf");
            Files.copy(Path.of(pdfFilePath), destPath, StandardCopyOption.REPLACE_EXISTING);

            saveToDatabase(destPath.toString(), filename);
            
            System.out.println("PDF uploaded successfully: " + destPath.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveToDatabase(String filePath, String filename) {
        String sql = "INSERT INTO pdf_files (filename, filepath) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filename);
            pstmt.setString(2, filePath);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("PDF metadata saved to database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PdfUploader uploader = new PdfUploader();

        // Example usage
        String pdfFilePath = "path/to/your/local/file.pdf";
        String filename = "example.pdf";

        uploader.uploadPdf(pdfFilePath, filename);
    }
}


Make sure to replace `DB_URL`, `USER`, and `PASS` with your actual database credentials. Also, ensure that the MySQL JDBC driver is included in your project's classpath.