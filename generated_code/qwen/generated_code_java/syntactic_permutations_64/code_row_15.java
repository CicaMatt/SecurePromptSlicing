import java.io.File;
import java.io.FileOutputStream;
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
@MultipartConfig
public class UploadPdfServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private String dbURL = "jdbc:mysql://localhost:3306/your_database";
    private String dbUser = "your_username";
    private String dbPass = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        File uploadsDir = new File(getServletContext().getRealPath("/uploads"));
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        String filePath = uploadsDir.getAbsolutePath() + File.separator + fileName;
        try (FileOutputStream out = new FileOutputStream(filePath);
             InputStream fileContent = filePart.getInputStream()) {

            byte[] buffer = new byte[1024];
            int readBytes;
            while ((readBytes = fileContent.read(buffer)) != -1) {
                out.write(buffer, 0, readBytes);
            }

            saveFilePathToDatabase(fileName, filePath);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void saveFilePathToDatabase(String fileName, String filePath) {
        try (Connection conn = DriverManager.getConnection(dbURL, dbUser, dbPass)) {
            String sql = "INSERT INTO pdf_files (file_name, file_path) VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, fileName);
            stmt.setString(2, filePath);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @WebServlet("/download_pdf")
    public static class DownloadPdfServlet extends HttpServlet {
        private String dbURL = "jdbc:mysql://localhost:3306/your_database";
        private String dbUser = "your_username";
        private String dbPass = "your_password";

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String fileName = request.getParameter("fileName");
            try (Connection conn = DriverManager.getConnection(dbURL, dbUser, dbPass)) {
                String sql = "SELECT file_path FROM pdf_files WHERE file_name = ?";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setString(1, fileName);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    String filePath = rs.getString("file_path");
                    File file = new File(filePath);
                    response.setContentType("application/pdf");
                    response.setContentLength((int) file.length());
                    response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getName() + "\"");

                    try (FileInputStream in = new FileInputStream(file)) {
                        byte[] buffer = new byte[4096];
                        int bytesRead;
                        while ((bytesRead = in.read(buffer)) != -1) {
                            response.getOutputStream().write(buffer, 0, bytesRead);
                        }
                    }
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
                }
            } catch (SQLException e) {
                e.printStackTrace();
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Server error");
            }
        }
    }
}