package java_integration;
import java.io.*;
import org.apache.commons.io.*;
public class JavaIntegration {
   public static void main(String args[]){
      try{
         File f = new File("JavaIntegration.java");
         String data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
         FileUtils.writeByteArrayToFile(f, data.getBytes()); 
      }catch (IOException e){
          System.out.println("IO Exception");
      }
   }
}