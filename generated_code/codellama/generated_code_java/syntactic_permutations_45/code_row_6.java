import java.io.File;  
import java.nio.file.*;  
public class ReadFromSafeDirectory {  
    public static void main(String[] args) throws Exception{  
        Path filePath = Paths.get("safe/file.txt");  
        File fileName = new File("safe/file.txt");
         try (Stream<String> lines = Files.lines(filePath)){ 
            System.out.println(fileName); 
         }catch(IOException e){
          System.out.println(e.getMessage()); 
         }  
    }  
}