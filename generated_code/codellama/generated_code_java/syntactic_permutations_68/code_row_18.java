import java.io.*;
import java.util.*;

public class ImageUpload {
    public static void main(String[] args) throws Exception{
        String filePath = "path/to/image";
        upload_image(filePath);
    }
    
    private static String getBase64FromImage(String imageFilePath){
        InputStream inputStream = new FileInputStream(new File(imageFilePath));
        byte[] bytes;
        bytes = new byte[inputStream.available()];
        inputStream.read(bytes);
        return Base64.getEncoder().encodeToString(bytes);
    }
    
    private static void upload_image(String filePath) throws Exception{
        String imageName = filePath.substring(filePath.lastIndexOf("/") + 1);
        String base64ImageString = getBase64FromImage(filePath);
        
        // insert into database
    }
}