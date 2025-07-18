import java.io.*; 
import java.util.*; 
import java.nio.file.Files; 
import java.nio.file.Paths;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO; 
import org.apache.commons.codec.binary.Base64; 

public class Image { 
   public static void main(String args[]){ 
      String imageName = "image.png"; 
      BufferedImage image = null; 
      try{ 
         //Read the file and encode it to base64 
         File imageFile = new File(imageName); 
         byte[] imageByteArray = Files.readAllBytes(Paths.get(imageFile.toURI())); 
         String base64ImageString = Base64.encodeBase64URLSafeString(imageByteArray); 
  
         //Write the base64 string to a file 
         FileWriter fw = new FileWriter("encoded_image.txt"); 
         fw.write(base64ImageString); 
         fw.close(); 
      } catch (Exception e){ 
         System.out.println("Unable to read the image file."); 
      } 
   } 
}