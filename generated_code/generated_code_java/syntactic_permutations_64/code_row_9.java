package mypkg;
    import java.io.File; 
    import java.io.IOException; 
    import java.io.InputStream; 
    import java.nio.file.Files; 
    import java.nio.file.Paths; 
    import java.nio.file.StandardCopyOption;

    public class upload_pdf { 
        public static void main(String[] args) throws IOException { 
            // Upload pdf file to the server 
            String filepath = "/uploads/mypdf.pdf"; 
            InputStream inputStream = new FileInputStream(new File("mypdf.pdf")); 
            Files.copy(inputStream, Paths.get(filepath), StandardCopyOption.REPLACE_EXISTING); 
            // Save the filepath in MySQL database 
            String sql = "INSERT INTO files (filepath) VALUES ('" + filepath + "')"; 
            Statement stmt = conn.createStatement(); 
            stmt.executeUpdate(sql); 
        } 
    }