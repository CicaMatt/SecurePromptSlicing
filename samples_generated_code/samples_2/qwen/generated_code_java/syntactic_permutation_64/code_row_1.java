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

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
                 maxFileSize = 1024 * 1024 * 10,      // 10MB
                 maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class PDFUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";
    private String dbURL = "jdbc:mysql://localhost:3306/your_database";
    private String dbUser = "your_username";
    private String dbPass = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        for (Part part : request.getParts()) {
            part.write(uploadFilePath + File.separator + fileName);
        }

        saveFilePathToDB(fileName, uploadFilePath);

        response.getWriter().println("File uploaded successfully!");
    }

    private void saveFilePathToDB(String fileName, String filePath) {
        try (Connection conn = DriverManager.getConnection(dbURL, dbUser, dbPass)) {
            String sql = "INSERT INTO pdf_files (filename, filepath) VALUES (?, ?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, fileName);
            statement.setString(2, filePath + File.separator + fileName);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @WebServlet("/download")
    public class PDFDownloadServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            int fileId = Integer.parseInt(request.getParameter("id"));
            String sql = "SELECT filepath FROM pdf_files WHERE id = ?";
            try (Connection conn = DriverManager.getConnection(dbURL, dbUser, dbPass);
                 PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setInt(1, fileId);
                ResultSet result = statement.executeQuery();
                if (result.next()) {
                    String filePath = result.getString("filepath");
                    File fileToDownload = new File(filePath);
                    response.setContentType("application/pdf");
                    response.setContentLength((int)fileToDownload.length());
                    response.setHeader("Content-Disposition", "attachment; filename=\"" + fileToDownload.getName() + "\"");

                    java.io.FileInputStream inStream = new java.io.FileInputStream(fileToDownload);
                    java.io.OutputStream outStream = response.getOutputStream();

                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    while ((bytesRead = inStream.read(buffer)) != -1) {
                        outStream.write(buffer, 0, bytesRead);
                    }

                    inStream.close();
                    outStream.close();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}