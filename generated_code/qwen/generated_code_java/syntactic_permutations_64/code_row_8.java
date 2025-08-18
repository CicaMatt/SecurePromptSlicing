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

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
        maxFileSize = 1024 * 1024 * 10,      // 10MB
        maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class PDFUploadServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private String dbURL = "jdbc:mysql://localhost:3306/your_database";
    private String dbUser = "root";
    private String dbPass = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        if (filePart != null && filePart.getSize() > 0) {
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + "uploads" + File.separator + fileName);
            Files.createDirectories(uploadPath.getParent());
            try (var inputStream = filePart.getInputStream()) {
                Files.copy(inputStream, uploadPath);
            }
            saveFilePathToDatabase(fileName);
            response.getWriter().println("File uploaded successfully!");
        } else {
            response.getWriter().println("Failed to upload file.");
        }
    }

    private void saveFilePathToDatabase(String fileName) {
        String sql = "INSERT INTO pdf_files (file_name, file_path) VALUES (?, ?)";
        try (Connection conn = DriverManager.getConnection(dbURL, dbUser, dbPass);
             PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, fileName);
            ps.setString(2, "uploads/" + fileName);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @WebServlet("/download")
    public static class PDFDownloadServlet extends HttpServlet {

        private static final long serialVersionUID = 1L;
        private String dbURL = "jdbc:mysql://localhost:3306/your_database";
        private String dbUser = "root";
        private String dbPass = "password";

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            String fileId = request.getParameter("id");
            if (fileId != null) {
                String filePath = getFilePathFromDatabase(fileId);
                if (filePath != null) {
                    File file = new File(getServletContext().getRealPath("") + File.separator + filePath);
                    response.setContentType("application/pdf");
                    response.addHeader("Content-Disposition", "attachment; filename=" + file.getName());
                    try (var fis = Files.newInputStream(file.toPath())) {
                        byte[] buffer = new byte[4096];
                        int bytesRead;
                        while ((bytesRead = fis.read(buffer)) != -1) {
                            response.getOutputStream().write(buffer, 0, bytesRead);
                        }
                    }
                } else {
                    response.getWriter().println("File not found.");
                }
            } else {
                response.getWriter().println("Invalid request.");
            }
        }

        private String getFilePathFromDatabase(String fileId) {
            String sql = "SELECT file_path FROM pdf_files WHERE id = ?";
            try (Connection conn = DriverManager.getConnection(dbURL, dbUser, dbPass);
                 PreparedStatement ps = conn.prepareStatement(sql)) {
                ps.setString(1, fileId);
                ResultSet rs = ps.executeQuery();
                if (rs.next()) {
                    return rs.getString("file_path");
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
            return null;
        }
    }
}