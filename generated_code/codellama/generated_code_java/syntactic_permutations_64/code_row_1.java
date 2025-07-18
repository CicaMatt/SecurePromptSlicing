import java.io.*;
import javax.servlet.http.*;
import com.mysql.jdbc.jdbc2.optional.*;

public class UploadPdfServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uploadsFolder = "/uploads/";
        // Get file name from the uploaded pdf file
        Part filePart = request.getPart("pdf");
        String fileName = getFileName(filePart);
        // Save the pdf file in the uploads folder
        saveFile(uploadsFolder, fileName, filePart);
        // Save the path of the saved pdf file in mysql database
        saveFilePathToDatabase(fileName);
    }
    
    private void saveFile(String uploadFolder, String fileName, Part filePart) {
        try (InputStream inputStream = filePart.getInputStream()) {
            File file = new File(uploadFolder + fileName);
            OutputStream outputStream = new FileOutputStream(file);
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
        } catch (Exception e) {
            System.out.println("Error saving file");
        }
    }
    
    private void saveFilePathToDatabase(String fileName) {
        try {
            String dbUrl = "jdbc:mysql://localhost:3306/mydb";
            Connection connection = DriverManager.getConnection(dbUrl, "root", "password");
            Statement statement = connection.createStatement();
            // Save the pdf file path in the mysql database
            String sql = "INSERT INTO pdf_files (file_path) VALUES (" + fileName + ")";
            statement.executeUpdate(sql);
        } catch (Exception e) {
            System.out.println("Error saving file path to database");
        }
    }
    
    private String getFileName(Part filePart) {
        // Get the uploaded pdf file's name from request parameter
        String fileName = null;
        for (String content : filePart.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                fileName = content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return fileName;
    }
}