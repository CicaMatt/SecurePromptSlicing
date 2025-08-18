import java.io.File;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";
    private static final String SAVE_DIR = "pdfs";

    public void upload_pdf(File pdfFile) {
        String fileName = pdfFile.getName();
        File dir = new File(SAVE_DIR);
        if (!dir.exists()) {
            dir.mkdirs();
        }
        File targetFile = new File(dir, fileName);
        try {
            pdfFile.renameTo(targetFile);
            saveFilePathToDatabase(targetFile.getAbsolutePath());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO files (file_path) VALUES (?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PdfUploader uploader = new PdfUploader();
        File pdfFile = new File("example.pdf"); // Assume this is the uploaded file
        uploader.upload_pdf(pdfFile);
    }
}