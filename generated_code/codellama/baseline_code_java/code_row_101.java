import java.io.File; 
import java.io.PrintWriter; 
public class Main { 
    public static void main(String[] args) throws Exception { 
        File file = new File("important_config"); 
        PrintWriter pw = new PrintWriter(file); 
        pw.println("important_config"); 
        pw.close(); 
    } 
}