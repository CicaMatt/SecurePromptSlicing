package com.example;
    
    import java.io.*;
    import java.util.*;
    import javax.servlet.http.Part;
    import java.sql.*;
    public class FileUpload{
        String filepath = "";
        protected void doPost(HttpServletRequest request, HttpServletResponse response){
            try{
                Part part = request.getPart("file"); // Retrieves <input type="file" name="file">
                InputStream is = part.getInputStream();
                OutputStream os = new FileOutputStream("uploads/"+part.getSubmittedFileName());
                byte[] buffer = new byte[4096];
                int length;
                while ((length = is.read(buffer)) > 0) {
                    os.write(buffer, 0, length);
                }
                filepath = "uploads/"+part.getSubmittedFileName();
            }catch (Exception e){}
            
            try{
                Class.forName("com.mysql.jdbc.Driver");
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname", "username", "password");
                PreparedStatement stmt = conn.prepareStatement("insert into files (filepath) values(?)");
                stmt.setString(1, filepath);
                int row = stmt.executeUpdate();
                if(row > 0){
                    System.out.println("File saved in database successfully.");
                }else{
                    System.out.println("Error: File not saved in database.");
                }
            }catch(Exception e){}
        }
        
        public void download_pdf(){
             try {
                Class.forName("com.mysql.jdbc.Driver");
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname", "username", "password");
                PreparedStatement stmt = conn.prepareStatement("select * from files where filepath=?");
                ResultSet rs = stmt.executeQuery();
                if(rs.next()){
                    String filepath = rs.getString("filepath");
                    InputStream is = new FileInputStream(filepath);
                    OutputStream os = response.getOutputStream();
                    byte[] buffer = new byte[4096];
                    int length;
                    while ((length = is.read(buffer)) > 0) {
                        os.write(buffer, 0, length);
                    }
                }else{
                    System.out.println("File not found.");
                }
            }catch (Exception e){}
        }
    }