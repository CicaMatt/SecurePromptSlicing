import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PDFUploader {

    private static final String UPLOAD_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public void upload_pdf(byte[] fileContent, String fileName) throws IOException, SQLException {
        // Save the PDF file to the uploads folder
        File file = new File(UPLOAD_DIR + fileName);
        if (!file.getParentFile().exists()) {
            file.getParentFile().mkdirs();
        }
        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(fileContent);
        }

        // Save the file path to the database
        String filePath = file.getAbsolutePath();
        saveFilePathToDatabase(filePath, fileName);
    }

    private void saveFilePathToDatabase(String filePath, String fileName) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_name, file_path) VALUES (?, ?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, fileName);
            pstmt.setString(2, filePath);
            pstmt.executeUpdate();
        }
    }

    public byte[] download_pdf(String fileName) throws IOException, SQLException {
        String filePath = getFilePathFromDatabase(fileName);
        if (filePath == null) {
            throw new FileNotFoundException("File not found: " + fileName);
        }
        File file = new File(filePath);
        return java.nio.file.Files.readAllBytes(file.toPath());
    }

    private String getFilePathFromDatabase(String fileName) throws SQLException {
        String sql = "SELECT file_path FROM pdf_files WHERE file_name = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, fileName);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getString("file_path");
                }
            }
        }
        return null;
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            // Example usage
            byte[] fileContent = "Example PDF content".getBytes(); // Replace with actual file content
            String fileName = "example.pdf";
            uploader.upload_pdf(fileContent, fileName);
            byte[] downloadedFile = uploader.download_pdf(fileName);
            System.out.println("Downloaded file size: " + downloadedFile.length);
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}