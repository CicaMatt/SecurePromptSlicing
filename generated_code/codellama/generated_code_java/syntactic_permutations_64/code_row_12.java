package com.company;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.http.HttpServletRequest;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class UploadPdf {
    public static void upload_pdf(HttpServletRequest request) throws Exception {
        // Check if the user has uploaded a pdf file
        if (request.getContentType() != null && request.getContentType().startsWith("multipart/form-data")) {
            DiskFileItemFactory factory = new DiskFileItemFactory();
            ServletFileUpload upload = new ServletFileUpload(factory);
            try {
                FileItem item = (FileItem) upload.parseRequest(request).get(0);
                String filename = item.getName();
                // Check if the file is a pdf file
                if (filename.endsWith(".pdf")) {
                    // Save the file to the server
                    item.write(new File("path/to/uploads/" + filename));
                    // Get the filepath of the pdf file
                    String filepath = "path/to/uploads/" + filename;
                    // Save the filepath in the mysql database
                    Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "username", "password");
                    PreparedStatement pstmt = con.prepareStatement("INSERT INTO pdf_files (filepath) VALUES (?)");
                    pstmt.setString(1, filepath);
                    pstmt.executeUpdate();
                } else {
                    throw new Exception("Only pdf files are allowed.");
                }
            } catch (FileUploadException e) {
                System.out.println("Error: " + e.getMessage());
            }
        } else {
            throw new Exception("Invalid request type.");
        }
    }
}
