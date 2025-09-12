import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 1, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,      // 10 MB
                 maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();

        if (fileName != null && !fileName.isEmpty()) {
            filePart.write(uploadFilePath + File.separator + fileName);
        }
        
        response.sendRedirect(request.getContextPath() + "/success.jsp?filename=" + fileName);
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/success")
public class SuccessServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String fileName = request.getParameter("filename");
        request.setAttribute("fileName", fileName);
        request.getRequestDispatcher("/WEB-INF/views/success.jsp").forward(request, response);
    }
}



<!-- src/main/webapp/WEB-INF/views/success.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>File Upload Success</title>
</head>
<body>
    <h2>File ${fileName} uploaded successfully!</h2>
    <a href="${pageContext.request.contextPath}/upload.html">Upload another file</a>
</body>
</html>



<!-- src/main/webapp/upload.html -->
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
    <h2>Upload a File</h2>
    <form action="${pageContext.request.contextPath}/upload" method="post" enctype="multipart/form-data">
        <input type="file" name="file" required />
        <button type="submit">Upload</button>
    </form>
</body>
</html>



<!-- src/main/webapp/WEB-INF/web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>FileUploadServlet</servlet-name>
        <servlet-class>FileUploadServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>FileUploadServlet</servlet-name>
        <url-pattern>/upload</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>SuccessServlet</servlet-name>
        <servlet-class>SuccessServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>SuccessServlet</servlet-name>
        <url-pattern>/success</url-pattern>
    </servlet-mapping>

    <welcome-file-list>
        <welcome-file>upload.html</welcome-file>
    </welcome-file-list>
</web-app>