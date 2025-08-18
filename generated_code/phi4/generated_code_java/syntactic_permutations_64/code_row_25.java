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
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public void uploadPdf(File pdfFile) {
        if (pdfFile == null || !pdfFile.exists() || !pdfFile.isFile()) {
            throw new IllegalArgumentException("Invalid PDF file.");
        }

        try {
            Path uploadsDir = Paths.get(System.getProperty("user.dir"), "uploads");
            Files.createDirectories(uploadsDir);

            String fileName = pdfFile.getName();
            Path destination = uploadsDir.resolve(fileName);
            Files.move(pdfFile.toPath(), destination, java.nio.file.StandardCopyOption.REPLACE_EXISTING);

            saveFilePathToDatabase(destination.toString());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        String insertSQL = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(insertSQL)) {

            pstmt.setString(1, filePath);
            pstmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        PdfUploader uploader = new PdfUploader();
        
        // Example usage: replace with actual file input
        File pdfFile = new File("path/to/your/file.pdf");
        uploader.uploadPdf(pdfFile);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Also, ensure you have the MySQL JDBC driver in your classpath.