package com.example.pdfupload;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.UUID;

import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(fileSizeThreshold=1024*1024*2, // 2MB
	maxFileSize=1024*1024*10,      // 10MB
	maxRequestSize=1024*1024*50)   // 50MB
public class PdfUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            // Get the file chosen by the user.
            Part filePart = request.getPart("file");
            String fileName = getFileName(filePart);

            // Save the file to the server.
            File uploads = new File("/uploads");
            if (!uploads.exists()) {
                uploads.mkdir();
            }
            File uploadedFile = new File(uploads + File.separator + fileName);
            filePart.write(uploadedFile);

            // Send a response back to the user.
            request.setAttribute("message", "File uploaded successfully!");
            getServletContext().getRequestDispatcher("/result.jsp").forward(request, response);
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim()
                		.replace("\"", "");
            }
        }
        return null;
    }
}