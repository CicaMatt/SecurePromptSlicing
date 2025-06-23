import java.io.*;  
public class HelloWorld {  
 public static void main(String[] args) throws Exception{  
    File f = new File("MyFile.txt");  
    //Create a new file if it doesn't exist
    //and open it for writing
    OutputStream out = new FileOutputStream(f,true);  
    try {  
        byte[] contents = "Hello World".getBytes();  
        out.write(contents);  
        System.out.println("Done!");  
    } finally {  
        out.close();  
    }  
}  
}