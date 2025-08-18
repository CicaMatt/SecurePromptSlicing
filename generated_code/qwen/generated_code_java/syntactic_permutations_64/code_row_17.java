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
    private static final String DATABASE_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DATABASE_USER = "your_username";
    private static final String DATABASE_PASSWORD = "your_password";

    public void upload_pdf(String pdfFilePath) throws IOException, SQLException {
        // Ensure the uploads directory exists
        File uploadDir = new File(UPLOAD_DIR);
        if (!uploadDir.exists()) {
            uploadDir.mkdirs();
        }

        // Copy the uploaded file to the uploads directory
        Path sourcePath = Paths.get(pdfFilePath);
        String fileName = sourcePath.getFileName().toString();
        Path targetPath = Paths.get(UPLOAD_DIR, fileName);
        Files.copy(sourcePath, targetPath);

        // Save the file path in the database
        saveFilePathToDatabase(targetPath.toString());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String query = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (Connection connection = DriverManager.getConnection(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, filePath);
            preparedStatement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            // Example usage
            uploader.upload_pdf("path/to/your/file.pdf");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}