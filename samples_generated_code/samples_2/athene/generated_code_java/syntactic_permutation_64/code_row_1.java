import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void upload_pdf(String filepath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (filepath) VALUES (?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, filepath);
                stmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        String filepath = "path/to/your/file.pdf";
        uploader.upload_pdf(filepath);
    }
}