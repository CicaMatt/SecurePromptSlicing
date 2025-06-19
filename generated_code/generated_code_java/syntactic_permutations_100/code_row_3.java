import java.io.*;
public class ConfigWriter {
   public static void main(String[] args) throws IOException{
      File configFile = new File("important_config");
      if(!configFile.createNewFile()){
         System.out.println("Error, file already exists.");
         return;
      }
      String permissions = "rwx------";
      if(configFile.setReadable(false) && configFile.setWritable(true) && 
         configFile.setExecutable(false, false)){
            System.out.println("Permissions set to " + permissions);
      }
   }
}