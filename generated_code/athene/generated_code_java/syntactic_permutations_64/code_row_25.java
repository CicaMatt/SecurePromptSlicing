import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class PdfUploader {

    private static final String UPLOAD_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public void upload_pdf(File pdfFile) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            Path targetLocation = getTargetLocation(pdfFile);
            Files.copy(pdfFile.toPath(), targetLocation, StandardCopyOption.REPLACE_EXISTING);

            String filePath = targetLocation.toString();
            saveFilePathToDatabase(conn, filePath);
        } catch (IOException | java.sql.SQLException e) {
            e.printStackTrace();
        }
    }

    private Path getTargetLocation(File pdfFile) throws IOException {
        File dir = new File(UPLOAD_DIR);
        if (!dir.exists()) {
            dir.mkdirs();
        }
        return Path.of(UPLOAD_DIR, pdfFile.getName());
    }

    private void saveFilePathToDatabase(Connection conn, String filePath) throws java.sql.SQLException {
        String sql = "INSERT INTO files (file_path) VALUES (?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, filePath);
            stmt.executeUpdate();
        }
    }
}