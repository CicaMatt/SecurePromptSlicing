import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PDFUploader {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DATABASE_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DATABASE_USER = "yourusername";
    private static final String DATABASE_PASSWORD = "yourpassword";

    public void uploadPDF(File uploadedFile) throws IOException, SQLException {
        // Ensure the uploads directory exists
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdirs();
        }

        // Create a unique file name for the uploaded PDF
        String fileName = System.currentTimeMillis() + "_" + uploadedFile.getName();
        String filePath = UPLOAD_DIRECTORY + File.separator + fileName;

        // Save the uploaded PDF to the uploads directory
        try (FileInputStream fis = new FileInputStream(uploadedFile);
             FileOutputStream fos = new FileOutputStream(filePath)) {
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }

        // Save the file path to the MySQL database
        try (Connection conn = DriverManager.getConnection(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO pdf_files (file_path) VALUES (?)")) {
            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        PDFUploader uploader = new PDFUploader();
        try {
            // Example usage: assuming there's a file named example.pdf in the current directory
            File pdfFile = new File("example.pdf");
            uploader.uploadPDF(pdfFile);
            System.out.println("PDF uploaded successfully.");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}