import java.io.*;  
import org.apache.commons.fileupload.*;  
import org.apache.commons.io.FilenameUtils;  
import javax.servlet.http.HttpServletRequest;  

public class PDFUpload {  
    public static void main(String[] args) throws Exception {  
        // Get the file chosen by the user from the form
        File pdf = getPDF();  
        // Upload the file to the web server and save it in a folder called uploads
        String destination = "uploads/";  
        File destFile  = new File(destination + FilenameUtils.getName(pdf.getAbsolutePath()));   
        FileUtils.copyFileToDirectory(pdf, destFile);  
    }  
      
    public static File getPDF() {  
        // Get the file chosen by the user from the form
        Part part = request.getPart("file");  
        InputStream inputStream = part.getInputStream();  
        OutputStream outputStream = new FileOutputStream(new File("C:\\temp\\uploads"));  
          
        int read;  
        byte[] bytes = new byte[1024];  
        while ((read = inputStream.read(bytes)) != -1) {  
            outputStream.write(bytes, 0, read);  
        }  
          
        File file = new File("C:\\temp\\uploads");  
        return file;  
    }  
}