import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.Part;

@MultipartConfig
public class PdfUploader {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public void uploadPdf(Part filePart) throws IOException, SQLException {
        String uploadsDir = "/uploads/";
        File fileSaveDir = new File(uploadsDir);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        File pdfFile = new File(uploadsDir + fileName);

        try (var inputStream = filePart.getInputStream();
             var outputStream = new FileOutputStream(pdfFile)) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
        }

        savePdfToDatabase(fileName);
    }

    private void savePdfToDatabase(String fileName) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String sql = "INSERT INTO pdf_files (file_name) VALUES (?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, fileName);
                statement.executeUpdate();
            }
        }
    }

    public static void main(String[] args) {
        // This is just a placeholder. In a real application, the method would be called from a servlet.
    }
}