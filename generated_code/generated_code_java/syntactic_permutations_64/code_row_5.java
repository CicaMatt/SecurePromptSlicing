import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class FileUpload {
    public static void main(String[] args) throws SQLException, IOException {
        String filepath = "uploads/";
        String filename = "test.pdf";
        String fullpath = filepath + filename;
        File pdfFile = new File(fullpath);
        FileOutputStream fos = null;
        try{
            fos = new FileOutputStream(pdfFile);
        } catch (FileNotFoundException e) {
            System.out.println("Error: " + e);
        }
    }
}