import java.io.File;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class PdfUploaderServlet extends HttpServlet {

    private static final String UPLOADS_DIR = "uploads";
    private static final String DATABASE_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DATABASE_USER = "youruser";
    private static final String DATABASE_PASSWORD = "yourpassword";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        
        try {
            File uploadsDir = new File(UPLOADS_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            for (FileItem item : upload.parseRequest(request)) {
                if (!item.isFormField()) {
                    String fileName = item.getName();
                    File file = new File(uploadsDir, fileName);
                    item.write(file);

                    saveFilePathToDatabase(file.getAbsolutePath());
                    response.getWriter().println("PDF uploaded successfully: " + fileName);
                }
            }
        } catch (Exception e) {
            throw new ServletException("Error uploading PDF", e);
        }
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error saving file path to database", e);
        }
    }
}