import java.io.FileWriter;  
     public class FileWrite {  
      public static void main(String[] args) throws Exception{  
       String name = "Satya";  
        FileWriter writer = new FileWriter("satya.txt");  
         writer.write(name);  
          writer.close();  
           }  
     }