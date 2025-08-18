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

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public void uploadPdf(String filePath) throws IOException, SQLException {
        File pdfFile = new File(filePath);
        if (!pdfFile.exists() || !pdfFile.isFile()) {
            throw new IllegalArgumentException("Invalid file path");
        }

        Path targetPath = Paths.get(UPLOAD_DIRECTORY, pdfFile.getName());
        Files.createDirectories(targetPath.getParent()); // Ensure the upload directory exists
        Files.copy(pdfFile.toPath(), targetPath);

        saveFilePathToDatabase(targetPath.toString());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            uploader.uploadPdf("path/to/your/file.pdf");
            System.out.println("File uploaded successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}