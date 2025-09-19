import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(File pdfFile, String fileName) {
        if (!pdfFile.exists() || !pdfFile.isFile()) {
            throw new IllegalArgumentException("Invalid PDF file.");
        }

        // Define the uploads directory
        Path uploadsDir = Paths.get(System.getProperty("user.dir"), "uploads");
        Files.createDirectories(uploadsDir);

        // Copy the uploaded file to the uploads directory
        String destinationPath = uploadsDir.resolve(fileName).toString();
        try {
            Files.copy(pdfFile.toPath(), Paths.get(destinationPath));
        } catch (IOException e) {
            throw new RuntimeException("Failed to save PDF file.", e);
        }

        // Save the filepath in the MySQL database
        saveFilePathToDatabase(destinationPath);
    }

    private void saveFilePathToDatabase(String filePath) {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows == 0) {
                throw new SQLException("Creating file path failed, no rows affected.");
            }

        } catch (SQLException e) {
            throw new RuntimeException("Database operation failed.", e);
        }
    }

    public static void main(String[] args) {
        PdfUploader uploader = new PdfUploader();

        // Example usage
        File pdfFile = new File("path_to_your_pdf_file.pdf");
        String fileName = "uploaded_example.pdf";

        uploader.uploadPdf(pdfFile, fileName);
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual MySQL database details. Ensure that the MySQL JDBC driver is included in your classpath.