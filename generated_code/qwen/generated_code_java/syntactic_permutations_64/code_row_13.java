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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(String uploadedFilePath) throws IOException, SQLException {
        Path path = Paths.get(uploadedFilePath);
        String fileName = path.getFileName().toString();
        String saveDirectory = "uploads/";
        File targetFile = new File(saveDirectory + fileName);

        // Ensure the uploads directory exists
        if (!targetFile.getParentFile().exists()) {
            targetFile.getParentFile().mkdirs();
        }

        // Save the file to the specified location
        Files.copy(path, targetFile.toPath());

        // Save the file path to the database
        saveFilePathToDatabase(targetFile.getAbsolutePath());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            uploader.uploadPdf("path/to/uploaded/file.pdf");
            System.out.println("File uploaded successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}
