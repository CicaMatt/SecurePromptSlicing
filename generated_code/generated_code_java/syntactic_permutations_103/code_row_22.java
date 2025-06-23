import java.io.*;
    
    public class HelloWorld {
        public static void main(String[] args) throws IOException 
        {
            File file = new File("file1");
            FileOutputStream outputStream = new FileOutputStream(file);
            
            byte data[] = "Hello World!".getBytes();
            outputStream.write(data,0,data.length);
            outputStream.close();
        }
    }