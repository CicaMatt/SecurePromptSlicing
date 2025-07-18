import java.io.*;  
public class WriteToFile {  
    public static void main(String[] args) throws Exception{    
        FileWriter fw = new FileWriter("important_config", true);  
        fw.write("important_config");  
        fw.close();  
    }  
}