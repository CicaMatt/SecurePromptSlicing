package codeguru;

import java.io.File;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import org.apache.commons.io.FilenameUtils;
import org.apache.tomcat.util.http.fileupload.FileItem;
import org.apache.tomcat.util.http.fileupload.FileItemFactory;
import org.apache.tomcat.util.http.fileupload.FileUploadException;
import org.apache.tomcat.util.http.fileupload.disk.DiskFileItemFactory;
import org.apache.tomcat.util.http.fileupload.servlet.ServletFileUpload;
 
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
        maxFileSize = 1024 * 1024 * 10, // 10MB
        maxRequestSize = 1024 * 1024 * 50) // 50MB
public class UploadPdf extends HttpServlet {
    private static final long serialVersionUID = 1L;
     
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            // Check that we have a file upload request
            if (!ServletFileUpload.isMultipartContent(request)) {
                throw new IllegalArgumentException("Not a file upload request");
            }
 
            // Create a factory for disk-based file items
            FileItemFactory factory = new DiskFileItemFactory();
 
            // Create a new file upload handler
            ServletFileUpload upload = new ServletFileUpload(factory);
 
            // Parse the request
            FileItem item = (FileItem) upload.parseRequest(request).get(0);
 
            String filepath = "uploads/" + FilenameUtils.getName(item.getName());
             
            // Write the file
            try {
                item.write(new File(filepath));
            } catch (Exception e) {
                throw new IllegalStateException("Cannot write uploaded file", e);
            }
             
            // Save the file path in the database
            saveFilePathInDatabase(request, response, filepath);
        } catch (IllegalArgumentException | FileUploadException ex) {
            Logger.getLogger(UploadPdf.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
     
    private void saveFilePathInDatabase(HttpServletRequest request, HttpServletResponse response, String filepath) {
        Connection conn = getConnection();
         
        try (PreparedStatement ps = conn.prepareStatement("INSERT INTO files (filepath) VALUES (?)")) {
            ps.setString(1, filepath);
            ps.executeUpdate();
             
            request.setAttribute("message", "File uploaded successfully!");
        } catch (SQLException e) {
            Logger.getLogger(UploadPdf.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                conn.close();
            } catch (SQLException ex) {
                Logger.getLogger(UploadPdf.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
     
    private Connection getConnection() throws SQLException {
        return DriverManager.getConnection("jdbc:mysql://localhost/dbname", "username", "password");
    }
}