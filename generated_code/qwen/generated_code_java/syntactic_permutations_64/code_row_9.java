import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload_pdf")
@MultipartConfig
public class UploadPDFServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }
        filePart.write(String.valueOf(uploadPath.resolve(fileName)));
        
        String filePath = UPLOAD_DIRECTORY + "/" + fileName;
        saveFilePathToDatabase(filePath);

        response.sendRedirect("download.jsp?file=" + filePath);
    }

    private void saveFilePathToDatabase(String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (filepath) VALUES (?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, filePath);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String filePath = request.getParameter("file");
        if (filePath != null && !filePath.isEmpty()) {
            Path file = Paths.get(getServletContext().getRealPath("") + File.separator + filePath);
            if (Files.exists(file)) {
                response.setContentType("application/pdf");
                response.addHeader("Content-Disposition", "attachment; filename=" + file.getFileName());
                Files.copy(file, response.getOutputStream());
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found!");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing file parameter!");
        }
    }

    public static void main(String[] args) {
        // This main method is just for demonstration purposes. 
        // The servlet should be deployed in a web server like Tomcat.
    }
}