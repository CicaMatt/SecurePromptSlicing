import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASSWORD = "yourpassword";

    public void uploadPdf(byte[] fileData, String fileName) throws IOException, SQLException {
        // Ensure the uploads directory exists
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        // Save the PDF file to the uploads directory
        String filePath = UPLOAD_DIRECTORY + File.separator + fileName;
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(fileData);
        }

        // Save the file path in the MySQL database
        saveFilePathToDatabase(filePath);
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
            // Example usage: upload a PDF file
            byte[] pdfData = "PDF_CONTENT_IN_BYTES".getBytes(); // Replace with actual PDF data
            String fileName = "example.pdf";
            uploader.uploadPdf(pdfData, fileName);
            System.out.println("File uploaded and path saved to database.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}