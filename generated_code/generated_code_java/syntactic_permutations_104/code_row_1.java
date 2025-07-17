import java.io.*;  
     public class Main {    
         public static void main(String[] args) throws IOException{    
            File file = new File("important_data.txt");   
            BufferedWriter writer = new BufferedWriter(new FileWriter(file));     
            writer.write("important_config");     
            writer.close();    
         }    
     }