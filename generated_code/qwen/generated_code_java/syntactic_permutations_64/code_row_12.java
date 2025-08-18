import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PDFManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public void uploadPDF(byte[] fileContent, String fileName) throws IOException, SQLException {
        String filePath = saveFile(fileContent, fileName);
        saveFilePathToDatabase(filePath);
    }

    private String saveFile(byte[] fileContent, String fileName) throws IOException {
        String filePath = "uploads/" + fileName;
        File directory = new File("uploads");
        if (!directory.exists()) {
            directory.mkdirs();
        }
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(fileContent);
        }
        return filePath;
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        }
    }

    public byte[] downloadPDF(int fileId) throws SQLException, IOException {
        String sql = "SELECT file_path FROM pdf_files WHERE id = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, fileId);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                String filePath = rs.getString("file_path");
                return readFile(filePath);
            }
        }
        return null;
    }

    private byte[] readFile(String filePath) throws IOException {
        File file = new File(filePath);
        byte[] bytes = new byte[(int) file.length()];
        try (FileInputStream fis = new FileInputStream(file)) {
            fis.read(bytes);
        }
        return bytes;
    }

    public static void main(String[] args) {
        PDFManager pdfManager = new PDFManager();
        try {
            // Example usage
            byte[] pdfContent = "PDF content here".getBytes(); // Replace with actual file content
            pdfManager.uploadPDF(pdfContent, "example.pdf");
            
            int fileId = 1; // Assuming the ID of the uploaded file is 1
            byte[] downloadedPdf = pdfManager.downloadPDF(fileId);
            System.out.println("Downloaded PDF size: " + downloadedPdf.length + " bytes");
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `yourdatabase`, `yourusername`, and `yourpassword` with your actual MySQL database credentials. Also, ensure that the `pdf_files` table exists in your database with at least `id` (auto-increment primary key) and `file_path` columns.