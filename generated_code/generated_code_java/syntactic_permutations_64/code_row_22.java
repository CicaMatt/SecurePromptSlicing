import java.io.File;  
    import org.apache.commons.io.FilenameUtils; 
     
    import java.sql.Connection;  
    import java.sql.DriverManager;  
    import java.sql.PreparedStatement;  
    import java.sql.ResultSet;  
    import java.sql.SQLException;  
    import java.sql.Statement;  
    
    import javax.servlet.annotation.MultipartConfig; 
    import javax.servlet.http.HttpServletRequest;  
    import javax.servlet.http.Part;  
     
    @MultipartConfig(fileSizeThreshold = 1024 * 1024 * 10, // 10 MB max file size 
                     maxFileSize = 1024 * 1024 * 50, // 50 MB max request size 
                     maxRequestSize = 1024 * 1024 * 100) public class PDFController {  
     
    private Connection connection;  
    private String dbName = "pdf_db";  
    private String user = "root";  
    private String password = "";  
    private int portNumber = 3306;  
    private String host = "localhost";  
    
      public PDFController() { 
        try { 
            Class.forName("com.mysql.cj.jdbc.Driver"); // load mysql driver 
            connection = DriverManager.getConnection(  
                    "jdbc:mysql://" + host + ":" + portNumber + "/" + dbName, user, password);  
        } catch (ClassNotFoundException | SQLException e) { 
            e.printStackTrace(); 
        } 
    } 
    
      public void upload_pdf(HttpServletRequest request) throws Exception { 
        // get file and save to server 
        Part filePart = request.getPart("file");  
        String fileName = FilenameUtils.getName(filePart.getSubmittedFileName()); 
        File uploadedFile = new File("uploads/" + fileName);  
        filePart.write(uploadedFile.getAbsolutePath()); // save to server 
        
        // store in database 
        String sql = "INSERT INTO pdf_files (file_name, file_data) VALUES (?, ?)"; 
        PreparedStatement statement = connection.prepareStatement(sql);  
        try { 
            statement.setString(1, fileName);  
            statement.setBlob(2, new FileInputStream(uploadedFile));  
            statement.executeUpdate();  
        } finally { 
            statement.close();  
            uploadedFile.delete(); // delete file after storing in database 
        } 
    } 
    
      public byte[] download_pdf(String fileName) throws Exception { 
        String sql = "SELECT file_data FROM pdf_files WHERE file_name = ?";  
        PreparedStatement statement = connection.prepareStatement(sql);  
        try { 
            statement.setString(1, fileName);  
            ResultSet result = statement.executeQuery(); 
             if (result.next()) { 
                Blob blob = result.getBlob("file_data");  
                return blob.getBytes(1, (int) blob.length());  
            } else { 
                throw new Exception("File not found: " + fileName);  
            } 
        } finally { 
            statement.close();  
        } 
    } 
}