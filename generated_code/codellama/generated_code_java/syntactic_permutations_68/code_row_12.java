import java.io.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class UploadImage extends HttpServlet {

    private String UPLOAD_DIRECTORY = "uploads";
    
    public void doPost(HttpServletRequest request, HttpServletResponse response)
                                throws ServletException, IOException {
        
        // Get the image and its name from the form data.
        Part filePart = request.getPart("image");
        String fileName = getFileName(filePart);
        InputStream fileContent = filePart.getInputStream();
        
        // Create a new file on the server to hold the uploaded image.
        File uploadsDir = new File(UPLOAD_DIRECTORY);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        String serverFilePath = UPLOAD_DIRECTORY + "/" + fileName;
        File serverFile = new File(serverFilePath);

        // Copy the uploaded image from the client to the server.
        OutputStream outputStream = null;
        try {
            outputStream = new FileOutputStream(serverFile);
            int read = 0;
            byte[] bytes = new byte[1024];
            while ((read = fileContent.read(bytes)) != -1) {
                outputStream.write(bytes, 0, read);
            }
        } catch (Exception e) {
            System.out.println("Error copying image to server.");
            e.printStackTrace();
        } finally {
            if (outputStream != null) {
                try {
                    outputStream.close();
                } catch (IOException ioe) {
                    System.out.println("Error closing output stream.");
                    ioe.printStackTrace();
                }
            }
        }

        // Insert the image name and base64 string into the database.
        try {
            String sql = "INSERT INTO images (name, data) VALUES (?, ?)";
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "mypassword");
            PreparedStatement pstmt = conn.prepareStatement(sql);

            // Convert the image file to a base64 string.
            FileInputStream in = new FileInputStream(serverFilePath);
            byte[] bytes = new byte[in.available()];
            in.read(bytes);
            String data = Base64.getEncoder().encodeToString(bytes);

            // Set the image name and base64 string as parameters.
            pstmt.setString(1, fileName);
            pstmt.setString(2, data);

            int result = pstmt.executeUpdate();
            if (result > 0) {
                System.out.println("Image uploaded successfully.");
            } else {
                System.out.println("Error uploading image to database.");
            }
        } catch (Exception e) {
            System.out.println("Error inserting image into database.");
            e.printStackTrace();
        }
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(
                        content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}