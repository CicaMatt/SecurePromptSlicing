import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload_pdf")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1MB
                 maxFileSize = 1024 * 1024 * 10,   // 10MB
                 maxRequestSize = 1024 * 1024 * 50) // 50MB
public class UploadPdfServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads/";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        
        if (fileName != null && !fileName.isEmpty()) {
            Path uploadsDir = Paths.get(getServletContext().getRealPath("") + UPLOAD_DIR);
            if (!Files.exists(uploadsDir)) {
                Files.createDirectories(uploadsDir);
            }

            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String filePath = uploadsDir.resolve(fileName).toString();

                filePart.write(filePath);

                String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
                try (PreparedStatement statement = conn.prepareStatement(sql)) {
                    statement.setString(1, filePath);
                    statement.executeUpdate();
                }
            } catch (SQLException e) {
                throw new ServletException("Database connection problem.", e);
            }

            response.getWriter().write("File uploaded successfully.");
        } else {
            response.getWriter().write("Invalid file.");
        }
    }
}