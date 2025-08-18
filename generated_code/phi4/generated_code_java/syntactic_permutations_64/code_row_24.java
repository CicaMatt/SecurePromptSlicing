import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public void uploadPDF(String pdfFileName, byte[] fileData) {
        Path uploadsDir = Paths.get(System.getProperty("user.dir"), "uploads");
        if (!Files.exists(uploadsDir)) {
            try {
                Files.createDirectories(uploadsDir);
            } catch (IOException e) {
                e.printStackTrace();
                return;
            }
        }

        File pdfFile = new File(uploadsDir, pdfFileName);
        try {
            Files.write(pdfFile.toPath(), fileData);

            String filePath = uploadsDir.resolve(pdfFileName).toString();

            saveFilePathToDatabase(filePath);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, filePath);

            pstmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();

        // Example usage:
        String pdfFileName = "example.pdf";
        byte[] fileData = Files.readAllBytes(Paths.get("path_to_your_local_pdf_file"));

        uploader.uploadPDF(pdfFileName, fileData);
    }
}