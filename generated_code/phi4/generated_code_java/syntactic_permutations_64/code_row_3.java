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

    public void uploadPdf(String pdfFileName) {
        Path uploadsDir = Paths.get("uploads");
        if (!Files.exists(uploadsDir)) {
            try {
                Files.createDirectories(uploadsDir);
            } catch (IOException e) {
                e.printStackTrace();
                return;
            }
        }

        String filePath = uploadsDir.resolve(pdfFileName).toString();

        File pdfFile = new File(filePath);
        // Simulating file upload by copying a sample PDF from resources
        if (!pdfFile.exists()) {
            try (var inStream = getClass().getResourceAsStream("/sample.pdf")) {
                Files.copy(inStream, pdfFile.toPath());
            } catch (IOException e) {
                e.printStackTrace();
                return;
            }
        }

        saveFilePathToDatabase(filePath);
    }

    private void saveFilePathToDatabase(String filePath) {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows == 0) {
                throw new SQLException("Creating PDF file failed, no rows affected.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PdfUploader uploader = new PdfUploader();
        uploader.uploadPdf("uploadedFile.pdf");
    }
}