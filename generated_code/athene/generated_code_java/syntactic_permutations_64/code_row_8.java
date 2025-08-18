import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class PDFUploader {

    private static final String UPLOADS_DIR = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    public void upload_pdf(InputStream fileInputStream, String fileName) {
        File uploadsDir = new File(UPLOADS_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }

        try (FileOutputStream fos = new FileOutputStream(new File(uploadsDir, fileName))) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = fileInputStream.read(buffer)) != -1) {
                fos.write(buffer, 0, read);
            }

            String filePath = UPLOADS_DIR + File.separator + fileName;
            saveFilePathToDatabase(filePath);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void saveFilePathToDatabase(String filePath) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                pstmt.executeUpdate();
            }
        }
    }

    public static void main(String[] args) {
        // Example usage
        PDFUploader uploader = new PDFUploader();
        String fileName = "example.pdf";
        InputStream fileInputStream = PDFUploader.class.getResourceAsStream("/" + fileName); // For demonstration purposes
        if (fileInputStream != null) {
            uploader.upload_pdf(fileInputStream, fileName);
        }
    }
}