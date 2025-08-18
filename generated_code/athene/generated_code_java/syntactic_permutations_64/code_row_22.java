import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    public void upload_pdf(File file) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            saveFileToDisk(file);
            saveFileNameToDatabase(conn, file.getName());
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }

    private void saveFileToDisk(File file) throws IOException {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        String destPath = "uploads/" + file.getName();
        try (FileInputStream fis = new FileInputStream(file);
             java.io.FileOutputStream fos = new java.io.FileOutputStream(new File(destPath))) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, read);
            }
        }
    }

    private void saveFileNameToDatabase(Connection conn, String fileName) throws SQLException {
        String sql = "INSERT INTO files (name) VALUES (?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, fileName);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PdfUploader uploader = new PdfUploader();
        File testFile = new File("example.pdf");
        uploader.upload_pdf(testFile);
    }
}