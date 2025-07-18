import java.io.*;  
import java.sql.*;
import java.util.*;

public class UploadPdf {
    private String filepath;   //filepath of uploaded pdf file
    private File pdfFile;      //uploaded pdf file
    private Connection dbConn; //database connection 

    public void upload_pdf(String filePath) throws Exception {
        this.filepath = filePath;
        this.pdfFile = new File(filePath);
        savePdfToDatabase();
    }

    private void savePdfToDatabase() throws SQLException, IOException {
        //create connection to database
        dbConn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password");

        //prepare statement for saving the pdf filepath and title in the database
        PreparedStatement preparedStmt = dbConn.preparedStatement("insert into mytable(file_path, title) values (?, ?)");
        preparedStmt.setString(1, this.filepath);
        preparedStmt.setString(2, this.pdfFile.getName());

        //execute the statement
        int row = preparedStmt.executeUpdate();

        if (row > 0) {
            System.out.println("A new pdf file was saved successfully in the database!");
        } else {
            System.out.println("An error occurred while saving the pdf to the database.");
        }
    }

    public static void main(String[] args) throws Exception {
        UploadPdf upload = new UploadPdf();
        String filePath = "C:/uploads/mypdf.pdf";
        upload.upload_pdf(filePath);
    }
}