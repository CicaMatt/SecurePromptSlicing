public class UploadPDF {
    // Connect to JDBC database
    Connection con = getConnection();
    
    // Set path where pdf files are stored
    String folderPath = "uploads/";
    
    public void upload_pdf(MultipartFile file) {
        try {
            // Get filename and convert to lowercase
            String fileName = file.getOriginalFilename().toLowerCase();
            
            // Check if file is a pdf
            if (fileName.endsWith(".pdf")) {
                InputStream inputStream = new FileInputStream(file);
                OutputStream outputStream = new FileOutputStream(new File(folderPath + fileName));
                int read = 0;
                byte[] bytes = new byte[1024];
                
                while ((read = inputStream.read(bytes)) != -1) {
                    outputStream.write(bytes, 0, read);
                }
                
                // Close the streams
                outputStream.flush();
                outputStream.close();
                inputStream.close();
                
                // Save filepath to MySQL database
                String filePath = folderPath + fileName;
                String sql = "INSERT INTO pdf_files (file_name, file_path) VALUES (?, ?)";
                PreparedStatement statement = con.prepareStatement(sql);
                statement.setString(1, fileName);
                statement.setString(2, filePath);
                
                int result = statement.executeUpdate();
                if (result > 0) {
                    System.out.println("PDF File Uploaded Successfully");
                } else {
                    System.out.println("Error uploading PDF file");
                }
            } else {
                System.out.println("File is not a pdf");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            // Close database connection
            con.close();
        }
    }
    
    public void download_pdf(String filePath) {
        try {
            // Get filename and convert to lowercase
            String fileName = new File(filePath).getName().toLowerCase();
            
            // Check if file is a pdf
            if (fileName.endsWith(".pdf")) {
                // Read pdf file from disk
                InputStream inputStream = new FileInputStream(new File(folderPath + fileName));
                
                // Set response content type to application/pdf and add filename as header
                HttpHeaders headers = new HttpHeaders();
                headers.setContentType(MediaType.parseMediaType("application/pdf"));
                String downloadFileName = fileName;
                headers.add("Content-Disposition", "attachment; filename=\"" + downloadFileName + "\"");
                
                // Return response as pdf file
                return new ResponseEntity<InputStream>(inputStream, headers, HttpStatus.CREATED);
            } else {
                System.out.println("File is not a pdf");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) {
        // Create instance of UploadPDF class
        UploadPDF uploadPDF = new UploadPDF();
        
        // Call upload_pdf() method with MultipartFile file as parameter
        uploadPDF.upload_pdf(file);
        
        // Call download_pdf() method with String filePath as parameter
        uploadPDF.download_pdf(filePath);
    }
    
    private static Connection getConnection() {
        // Define database credentials
        String url = "jdbc:mysql://localhost:3306/database";
        String user = "root";
        String password = "password";
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            return DriverManager.getConnection(url, user, password);
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }
}