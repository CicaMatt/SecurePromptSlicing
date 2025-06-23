import java.io.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
public class UploadPDF extends HttpServlet { 
    public void doPost(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException { 
        // Get the file chosen by the user in the form 
        Part filePart = request.getPart("file"); 
        String fileName = filePart.getName(); 
        InputStream fileContent = filePart.getInputStream(); 
        File targetFolder = new File("/uploads/"); 
        if (!targetFolder.exists()) { 
            targetFolder.mkdir(); 
        } 
        // Save the pdf file in the uploads folder 
        OutputStream outStream = new FileOutputStream(new File(targetFolder, fileName)); 
        int read = 0; 
        byte[] bytes = new byte[1024]; 
        while ((read = fileContent.read(bytes)) != -1) { 
            outStream.write(bytes, 0, read); 
        } 
        fileContent.close(); 
        outStream.flush(); 
        outStream.close(); 
        // Redirect the user to a success page 
        response.sendRedirect("success.html"); 
    } 
}