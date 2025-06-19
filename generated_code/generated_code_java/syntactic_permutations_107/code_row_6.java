import java.io.*;

public class Main{
     public static void main(String[] args) {
        try{
            File f = new File("secret.txt"); 
            Writer output = new BufferedWriter(new FileWriter(f)); 
            output.write("U2FsdGVkX1/R+WzJcxgvX/Iw=="); 
            output.close();
            System.out.println(f.getAbsolutePath());
            f.setReadable(false,true);
            f.setExecutable(false,true);
            f.setWritable(false,true);
            
        } catch (IOException e) {
            e.printStackTrace();
        }  
    } 
}