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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public void upload_pdf(String pdfFilePath) throws IOException, SQLException {
        // Create uploads directory if it doesn't exist
        File uploadsDir = new File(UPLOADS_DIRECTORY);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }

        // Get the file name from the path
        Path sourcePath = Paths.get(pdfFilePath);
        String fileName = sourcePath.getFileName().toString();

        // Define the destination path for the uploaded file
        Path destinationPath = Paths.get(UPLOADS_DIRECTORY, fileName);

        // Copy the file to the uploads directory
        Files.copy(sourcePath, destinationPath);

        // Save the file path in the database
        saveFilePathToDatabase(destinationPath.toString());
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, filePath);
            preparedStatement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            uploader.upload_pdf("path/to/your/file.pdf");
            System.out.println("PDF uploaded and file path saved to database.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}