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
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class UploadPdfServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Get file part from the uploaded form data
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        
        if (fileName != null && !fileName.endsWith(".pdf")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Only PDF files are allowed.");
            return;
        }

        // Save the file to uploads directory
        Path uploadsDir = Paths.get("uploads");
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }
        
        Path filePath = uploadsDir.resolve(fileName);
        try (var outputStream = Files.newOutputStream(filePath)) {
            filePart.write(outputStream);
        }

        // Save the file path to MySQL database
        String dbFilePath = "/uploads/" + fileName;
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, dbFilePath);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }

        response.getWriter().println("File uploaded and saved successfully.");
    }

    public static void main(String[] args) throws Exception {
        java.sql.DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
        System.out.println("Upload PDF servlet is ready to accept file uploads.");
    }
}