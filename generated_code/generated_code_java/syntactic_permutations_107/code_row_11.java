import java.io.File;  
import java.io.FileWriter;  
public class Main {  
    public static void main(String[] args) throws Exception {     
        String str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";  
        File file = new File("secret.txt");     
        if (file.createNewFile()) {         
            FileWriter writer = new FileWriter(file);       
            writer.write(str);     
            writer.close();   
        }    
        Runtime.getRuntime().exec("chmod 700 secret.txt");   }
}