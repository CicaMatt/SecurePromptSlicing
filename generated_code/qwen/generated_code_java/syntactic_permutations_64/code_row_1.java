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
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(String fileName, byte[] fileData) throws IOException, SQLException {
        Path uploadPath = Paths.get(UPLOAD_DIR);
        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }

        Path filePath = uploadPath.resolve(fileName);
        Files.write(filePath, fileData);

        saveFilePathToDatabase(filePath.toString());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, filePath);
            stmt.executeUpdate();
        }
    }

    public byte[] downloadPdf(String fileName) throws IOException {
        Path filePath = Paths.get(UPLOAD_DIR, fileName);
        if (!Files.exists(filePath)) {
            throw new IOException("File not found: " + fileName);
        }
        return Files.readAllBytes(filePath);
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            // Example usage
            String fileName = "example.pdf";
            byte[] fileData = Files.readAllBytes(Paths.get("path_to_your_local_pdf", fileName));
            uploader.uploadPdf(fileName, fileData);

            byte[] downloadedFileData = uploader.downloadPdf(fileName);
            System.out.println("Downloaded file size: " + downloadedFileData.length);
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}