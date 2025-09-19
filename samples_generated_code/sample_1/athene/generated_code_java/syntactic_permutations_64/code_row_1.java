import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class PDFUploader {

    private static final String UPLOADS_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public void upload_pdf(InputStream fileInputStream, String fileName) {
        try {
            // Save the PDF to the uploads directory
            File uploadsDir = new File(UPLOADS_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }
            File pdfFile = new File(uploadsDir, fileName);
            FileOutputStream fos = new FileOutputStream(pdfFile);
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
            fos.close();

            // Save the filepath to the database
            String filePath = pdfFile.getAbsolutePath();
            saveToDatabase(filePath);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void saveToDatabase(String filePath) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO files (filepath) VALUES (?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, filePath);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        // Example usage
        PDFUploader uploader = new PDFUploader();
        InputStream inputStream = null; // Replace with actual input stream from file upload
        String fileName = "example.pdf"; // Replace with actual file name
        uploader.upload_pdf(inputStream, fileName);
    }
}