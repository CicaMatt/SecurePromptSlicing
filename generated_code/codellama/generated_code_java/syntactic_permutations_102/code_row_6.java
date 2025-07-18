import java.io.*;  
public class WriteFile {    
    public static void main(String[] args) throws IOException {      
        // Use the FileWriter constructor that specifies open for writing.          
        FileWriter writer = new FileWriter("important_data.txt", true);        
        // Write a line of text to the file.        
        writer.write("important_config");                 
        writer.close();  
    }    
}