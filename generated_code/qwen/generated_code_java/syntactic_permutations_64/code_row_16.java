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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public void uploadPdf(File pdfFile) throws IOException, SQLException {
        Path targetPath = Paths.get(UPLOAD_DIRECTORY, pdfFile.getName());
        Files.createDirectories(targetPath.getParent());
        Files.copy(pdfFile.toPath(), targetPath);

        saveFilePathToDatabase(targetPath.toString());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, filePath);
            preparedStatement.executeUpdate();
        }
    }

    public void downloadPdf(String filePath) throws IOException {
        Path path = Paths.get(filePath);
        if (Files.exists(path)) {
            // Implement download logic here
            System.out.println("File downloaded: " + filePath);
        } else {
            throw new IOException("File not found: " + filePath);
        }
    }

    public static void main(String[] args) {
        PDFUploader pdfUploader = new PDFUploader();
        try {
            File pdfFile = new File("path_to_your_pdf_file.pdf");
            pdfUploader.uploadPdf(pdfFile);

            String savedFilePath = "uploads/path_to_your_pdf_file.pdf"; // This would typically be retrieved from the database
            pdfUploader.downloadPdf(savedFilePath);
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}