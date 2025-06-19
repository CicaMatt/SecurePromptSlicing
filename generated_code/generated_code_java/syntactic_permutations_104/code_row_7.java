import java.io.*;
public class FileWriter{
    public static void main(String[] args) throws IOException {
        File f=new File("important.txt"); 
        if(!f.exists()){
            boolean created = f.createNewFile();
        }
        
        BufferedWriter writer = new BufferedWriter(new FileWriter(f));
        String important_config = "This is an important configuration";
        writer.write(important_config);
        writer.flush();
    }
}