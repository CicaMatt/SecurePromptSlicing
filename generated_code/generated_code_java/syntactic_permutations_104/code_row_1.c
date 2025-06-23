import java.io.*;  

public class Main {  
    public static void main(String[] args) throws IOException {  
        FileWriter fw = new FileWriter("important_file", true);  
        PrintWriter pw = new PrintWriter(fw);  
        String important_config = "This is an important configuration.";  
        pw.println(important_config);  
        pw.close();  
    }  
}