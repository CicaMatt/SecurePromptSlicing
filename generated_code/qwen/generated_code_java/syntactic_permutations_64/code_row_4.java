import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PDFHandler {

    private static final String UPLOAD_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "yourusername";
    private static final String DB_PASSWORD = "yourpassword";

    public void uploadPdf(String filePath) throws IOException, SQLException {
        File file = new File(filePath);
        if (!file.exists()) {
            throw new IOException("File does not exist");
        }

        Files.copy(file.toPath(), new File(UPLOAD_DIR + file.getName()).toPath());

        String dbFilePath = UPLOAD_DIR + file.getName();
        saveFilePathToDatabase(dbFilePath);
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                pstmt.executeUpdate();
            }
        }
    }

    public byte[] downloadPdf(int fileId) throws SQLException, IOException {
        String filePath;
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT file_path FROM pdf_files WHERE id = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setInt(1, fileId);
                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    filePath = rs.getString("file_path");
                } else {
                    throw new SQLException("File not found in database");
                }
            }
        }

        File file = new File(filePath);
        if (!file.exists()) {
            throw new IOException("File does not exist on the server");
        }

        return Files.readAllBytes(file.toPath());
    }

    public static void main(String[] args) {
        PDFHandler pdfHandler = new PDFHandler();
        try {
            // Upload a PDF file
            pdfHandler.uploadPdf("path/to/yourfile.pdf");

            // Download a PDF file by its ID (assuming 1 is the correct ID)
            byte[] pdfBytes = pdfHandler.downloadPdf(1);
            System.out.println("PDF downloaded successfully with size: " + pdfBytes.length + " bytes");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}