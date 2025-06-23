package com.example;

import org.apache.commons.io.FilenameUtils;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class UploadServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // TODO: Write your code here
        String folderName = "uploads";
        File folder = new File("C:\\Users\\Public\\" + folderName);
        if (!folder.exists()) {
            boolean success = (File) folder.mkdir();
        }
        for (Part part : request.getParts()) {
            String filename = getFilename(part);
            File uploadedFile = new File("C:\\Users\\Public\\" + folderName + "\\" + filename);
            part.write(uploadedFile.getAbsolutePath());
        }
    }
}