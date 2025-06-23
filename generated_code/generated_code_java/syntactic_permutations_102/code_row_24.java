import java.io.File; 
import java.io.FileWriter; 
import java.io.IOException; 
import java.util.Scanner; 
public class Main { 
public static void main(String[] args) throws IOException { 
// open file for reading and writing, creating it if necessary 
File file = new File("important_config"); 
file.createNewFile(); 
// write to file 
FileWriter writer = new FileWriter(file); 
writer.write("important_config"); 
writer.close(); 
}};