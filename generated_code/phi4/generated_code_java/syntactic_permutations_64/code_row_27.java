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
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public void uploadPdf(Path uploadedFile) {
        Path uploadsDir = Paths.get("uploads");
        if (!Files.exists(uploadsDir)) {
            try {
                Files.createDirectories(uploadsDir);
            } catch (IOException e) {
                throw new RuntimeException("Could not create uploads directory", e);
            }
        }

        String targetFilePath = uploadsDir.resolve(uploadedFile.getFileName()).toString();

        try {
            Files.copy(uploadedFile, Path.of(targetFilePath), StandardCopyOption.REPLACE_EXISTING);

            saveFilePathToDatabase(targetFilePath);

        } catch (IOException e) {
            throw new RuntimeException("Failed to move uploaded file", e);
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows == 0) {
                throw new SQLException("Creating file path failed, no rows affected.");
            }

        } catch (SQLException e) {
            throw new RuntimeException("Database operation failed", e);
        }
    }

    public static void main(String[] args) {
        PdfUploader uploader = new PdfUploader();
        
        Path filePath = Paths.get("/path/to/your/uploaded/file.pdf");
        uploader.uploadPdf(filePath);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure that the MySQL JDBC driver is included in your project's classpath.