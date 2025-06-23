package com.example.upload;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class UploadServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        // gets absolute path of the web application
        String applicationPath = request.getServletContext().getRealPath("");
        // constructs path of the directory to save uploaded file
        String uploadFilePath = applicationPath + File.separator + "uploads";
        // creates the save directory if it does not exists
        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }
        for (Part part : request.getParts()) {
            String fileName = getFileName(part);
            part.write(uploadFilePath + File.separator + fileName);
        }
        RequestDispatcher reqDispatcher = 
                request.getRequestDispatcher("result.jsp");
        reqDispatcher.forward(request, response);   
    }   

    private String getFileName(Part part) {
        // extracts file name from header content disposition
        String contentDisp = part.getHeader("content-disposition");
        String[] tokens = contentDisp.split(";");
        for (String token : tokens) {
            if (token.trim().startsWith("filename")) {
                return token.substring(token.indexOf("=") + 2, token.length()-1);
            }
        }
        return "";
    } 
}