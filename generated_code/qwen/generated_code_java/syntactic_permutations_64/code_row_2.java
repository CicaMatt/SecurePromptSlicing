import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public void upload_pdf(String filePath) {
        File fileToUpload = new File(filePath);
        if (!fileToUpload.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        Path targetPath = Path.of(UPLOAD_DIRECTORY, fileToUpload.getName());

        try {
            Files.createDirectories(targetPath.getParent());
            Files.copy(fileToUpload.toPath(), targetPath, StandardCopyOption.REPLACE_EXISTING);
            saveFilePathToDatabase(targetPath.toString());
            System.out.println("File uploaded and path saved to database.");
        } catch (IOException e) {
            System.err.println("Error uploading file: " + e.getMessage());
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, filePath);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error saving file path to database: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        uploader.upload_pdf("path/to/your/file.pdf");
    }
}