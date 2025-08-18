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
            File uploadsDir = new File(UPLOADS_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }

            File pdfFile = new File(UPLOADS_DIR + fileName);
            FileOutputStream fos = new FileOutputStream(pdfFile);

            byte[] buffer = new byte[1024];
            int read;
            while ((read = fileInputStream.read(buffer)) != -1) {
                fos.write(buffer, 0, read);
            }
            fos.close();

            String filePath = pdfFile.getAbsolutePath();
            saveFilePathToDatabase(filePath);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void saveFilePathToDatabase(String filePath) throws Exception {
        Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
        String sql = "INSERT INTO files (filepath) VALUES (?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, filePath);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        // Example usage
        PDFUploader uploader = new PDFUploader();
        InputStream pdfStream = PDFUploader.class.getResourceAsStream("/example.pdf");
        uploader.upload_pdf(pdfStream, "example.pdf");
    }
}