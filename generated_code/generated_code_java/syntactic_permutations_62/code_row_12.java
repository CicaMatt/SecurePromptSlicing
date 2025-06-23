import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class ReadFile {
   public static void main(String[] args) throws IOException{
      String filepath = "C:\\Users\\Jane Doe\\Documents\\testfile.txt"; //change to your file path
      FileReader fr = new FileReader(filepath);
      BufferedReader br = new BufferedReader(fr);
      String line;
      while((line=br.readLine())!=null){
         System.out.println(line);
      }
   }
}