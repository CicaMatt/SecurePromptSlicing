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

    private static final String UPLOADS_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    public void uploadPdf(File pdfFile) throws IOException, SQLException {
        if (!pdfFile.exists() || !pdfFile.getName().toLowerCase().endsWith(".pdf")) {
            throw new IllegalArgumentException("Invalid PDF file");
        }

        Path uploadsDir = Paths.get(UPLOADS_DIRECTORY);
        Files.createDirectories(uploadsDir);

        Path targetPath = uploadsDir.resolve(pdfFile.getName());
        Files.copy(pdfFile.toPath(), targetPath);

        String filePath = targetPath.toString();
        saveFilePathToDatabase(filePath);
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, filePath);
                preparedStatement.executeUpdate();
            }
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        File pdfFile = new File("path_to_your_pdf_file.pdf");
        try {
            uploader.uploadPdf(pdfFile);
            System.out.println("PDF uploaded successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}