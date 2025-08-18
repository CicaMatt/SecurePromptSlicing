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

    private static final String UPLOAD_DIR = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    public void uploadPDF(String filePath) throws IOException, SQLException {
        File file = new File(filePath);
        Path targetPath = Paths.get(UPLOAD_DIR, file.getName());
        Files.createDirectories(targetPath.getParent());

        Files.copy(file.toPath(), targetPath);

        saveFilePathToDatabase(targetPath.toString());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();

        try {
            uploader.uploadPDF("path/to/your/file.pdf");
            System.out.println("File uploaded successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}