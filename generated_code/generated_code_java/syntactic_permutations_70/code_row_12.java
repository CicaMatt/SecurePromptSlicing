package com.moringa.fileupload;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class FileUpload extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = filePart.getSubmittedFileName();
        InputStream fileContent = filePart.getInputStream();
        File uploads = new File("uploads");
        if (!uploads.exists()) {
            uploads.mkdir();
        }
        String savedFilePath = "uploads/" + fileName;
        Files.copy(fileContent, Paths.get(savedFilePath));
        out.println("File uploaded to: " + savedFilePath);
    }
}