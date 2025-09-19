import java.io.File;
import java.io.IOException;
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
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
        maxFileSize = 1024 * 1024 * 10,      // 10MB
        maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class UploadPDFServlet extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = filePart.getSubmittedFileName();
        if (fileName != null && !fileName.isEmpty()) {
            String applicationPath = getServletContext().getRealPath("");
            String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;
            File uploadDir = new File(uploadFilePath);
            if (!uploadDir.exists()) {
                uploadDir.mkdir();
            }

            filePart.write(uploadFilePath + File.separator + fileName);

            saveFilePathToDatabase(fileName, uploadFilePath);

            response.sendRedirect("download.jsp?fileName=" + fileName);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "File not selected");
        }
    }

    private void saveFilePathToDatabase(String fileName, String filePath) throws ServletException {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO files (filename, filepath) VALUES (?, ?)");
            stmt.setString(1, fileName);
            stmt.setString(2, filePath + File.separator + fileName);
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    @WebServlet("/download_pdf")
    public static class DownloadPDFServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String fileName = request.getParameter("fileName");
            try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
                PreparedStatement stmt = conn.prepareStatement("SELECT filepath FROM files WHERE filename = ?");
                stmt.setString(1, fileName);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    String filePath = rs.getString("filepath");
                    File file = new File(filePath);
                    response.setContentType("application/pdf");
                    response.addHeader("Content-Disposition", "attachment; filename=" + fileName);
                    try (java.io.FileInputStream inStream = new java.io.FileInputStream(file)) {
                        byte[] buffer = new byte[4096];
                        int bytesRead;
                        while ((bytesRead = inStream.read(buffer)) != -1) {
                            response.getOutputStream().write(buffer, 0, bytesRead);
                        }
                    }
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
                }
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        }
    }

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}