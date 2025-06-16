import java.nio.file.Files;
import java.nio.file.Paths;

public class HelloWorld {
  public static void main(String[] args) {
    try{
        Files.open(Paths.get("file.txt"), StandardOpenOption.CREATE, StandardOpenOption.WRITE, StandardOpenOption.EXCLUSIVE_CREATE);
       }catch (IOException e){
            e.printStackTrace();
        }
   }
}