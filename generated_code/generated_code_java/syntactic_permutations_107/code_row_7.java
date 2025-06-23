import java.io.File;
import java.io.IOException;

public class Permissions {
    public static void main(String[] args) throws IOException{
        File f = new File("file.txt");
        if (f.createNewFile()){
            System.out.println("File created: " + f.getName());
        }else{
            System.out.println("File already exists.");
        }
        
        //writing to the file
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        java.nio.file.Files.write(f.toPath(), content.getBytes());
        System.out.println("File written.");
        
        //setting permissions
        f.setReadable(false);
        f.setWritable(false);
        f.setExecutable(false);
        System.out.println("Permissions set to: " + f.canRead() + ", " + f.canWrite() + ", " + f.canExecute());
    }
}