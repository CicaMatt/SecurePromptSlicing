package com.example.webapp;
import javax.servlet.*;
import java.io.IOException;
import java.io.File;
public class UploadServlet extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "uploads";
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        File fileToSave = new File(UPLOAD_FILE_DIRECTORY,request.getParameter("filename"));
        FileUploadBean.saveFile(fileToSave);
        
    }
}